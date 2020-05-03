unit DBJson;

interface

uses
  System.SysUtils, System.Classes, System.Variants, Data.DB, Data.Win.ADODB,
  Datasnap.DBClient, System.TypInfo, Soap.EncdDecd, superobject;

type
  TTableJson = class
  private
    // JSON���뽨���ֵ���Ϣ�����ܴ������ݼ����ֶ���Ϣ��
    const cstFieldIndex = 'FieldIndex';
    const cstFieldName  = 'FieldName';
    const cstFieldType  = 'FieldType';
    const cstFieldSize  = 'FieldSize';
    const cstRequired   = 'Required';
    const cstCols       = 'Cols';
    const cstData       = 'Data';
  public
    class function DataSetToJson(DataSet: TDataSet): string;
    class function JsonToDataSet(DataSet: TDataSet; Json: ISuperObject): Boolean;
    class function ImportDataFromJson(DataSet: TDataSet; DataJson: ISuperObject): Integer;
    class function CreateFieldByJson(Fields: TFieldDefs; ColsJson: ISuperObject): Boolean;
    class function GetValue(Json: ISuperObject; const Name: string): Variant;
    class function CreateJsonValue(Json: ISuperObject; const Name: string; const Value: Variant): Boolean;
    class function CreateJsonValueByField(Json: ISuperObject; Field: TField): Boolean;
    class function GetValue2Field(Field: TField; JsonValue: ISuperObject): Variant;
  end;

implementation

{ TTableJSon }

class function TTableJson.JsonToDataSet(DataSet: TDataSet; Json: ISuperObject): Boolean;
var
  ColsJson: ISuperObject;
begin
  Result := False;
  if DataSet is TCustomClientDataSet then
  begin
    with DataSet AS TCustomClientDataSet do
    begin
      if Json = nil then Exit;
      Close;
      Data := Null;
      //�����ֶ�
      ColsJson := Json.O[cstCols];
      CreateFieldByJson(FieldDefs,ColsJson);
      if FieldDefs.Count > 0 then
        CreateDataSet;

      ImportDataFromJSon(DataSet,Json.O[cstData]);

      Result := True;
    end;
  end
  else
  if DataSet is TADODataSet then
  begin
    with  DataSet as TADODataSet do
    begin
      if Json = nil then Exit;
      Close;
      //�����ֶ�
      ColsJson := Json.O[cstCols];
      CreateFieldByJson(FieldDefs,ColsJson);
      if FieldDefs.Count > 0 then
        CreateDataSet;

      ImportDataFromJSon(DataSet,Json.O[cstData]);
      Result := True;
    end;
  end;
end;

class function TTableJson.CreateFieldByJson(Fields: TFieldDefs; ColsJson: ISuperObject): Boolean;
var
  SubJson: ISuperObject;
  ft: TFieldType;
begin
  Result := False;
  Fields.DataSet.Close;
  Fields.Clear;
  for SubJson in ColsJson do
  begin
    ft := TFieldType(GetEnumValue(TypeInfo(TFieldType),'ft'+SubJson.S[cstFieldType]));
    if ft = ftAutoInc then //�����ֶβ���¼�룬�������
      ft := ftInteger;
    Fields.Add(SubJson.S[cstFieldName],ft,SubJson.I[cstFieldSize],SubJson.B[cstRequired]);
  end;
  Result := True;
end;

class function TTableJson.CreateJsonValue(Json: ISuperObject; const Name: string; const Value: Variant): Boolean;
begin
  Result := False;
  Json.O[Name] := SO(Value);
  Result := True;
end;

class function TTableJson.CreateJsonValueByField(Json: ISuperObject; Field: TField): Boolean;
begin
  Result := False;

  if Field is TDateTimeField then
    Json.O[Field.FieldName] := SO(Field.AsDateTime)
  else
  if Field is TBlobField then
    Json.S[Field.FieldName] := EncodeString(Field.AsString)
  else
  if Field is TNumericField then
    Json.O[Field.FieldName] := SO(Field.AsFloat)
  else
    Json.O[Field.FieldName] := SO(Field.Value);

  Result := True;
end;

class function TTableJson.GetValue(Json: ISuperObject; const Name: string): Variant;
begin
  case Json.DataType of
    stNull:     Result := Null;
    stBoolean:  Result := Json.B[Name];
    stDouble:   Result := Json.D[Name];
    stCurrency: Result := Json.C[Name];
    stInt:      Result := Json.I[Name];
    stString:   Result := Json.S[Name];
  end;
end;

class function TTableJson.GetValue2Field(Field: TField; JsonValue:ISuperObject): Variant;
begin
  if JsonValue.DataType = stNull then
    Result := Null
  else if Field is TDateTimeField then
    Result := JavaToDelphiDateTime(JsonValue.AsInteger)
  else if (Field is TIntegerField) or (Field is TLargeintField) then
    Result := JsonValue.AsInteger
  else if Field is TNumericField then
    Result := JsonValue.AsDouble
  else if Field is TBooleanField then
    Result := JsonValue.AsBoolean
  else if Field is TStringField then
    Result := JsonValue.AsString
  else if Field is TBlobField then
    Result := DecodeString(JsonValue.AsString)
end;

class function TTableJson.ImportDataFromJson(DataSet: TDataSet; DataJson: ISuperObject): Integer;
var
  SubJson: ISuperObject;
  i: Integer;
  iter: TSuperObjectIter;
begin
  if not DataSet.Active then
    DataSet.Open;
  DataSet.DisableControls;
  try
    for SubJson in DataJson do
    begin
      DataSet.Append;
      if ObjectFindFirst(SubJson,iter) then
      begin
         repeat
           if DataSet.FindField(iter.Ite.Current.Name)<>nil then
             DataSet.FindField(iter.Ite.Current.Name).Value := GetValue2Field(DataSet.FindField(iter.Ite.Current.Name),iter.Ite.Current.Value);
         until not ObjectFindNext(iter) ;
      end;
      DataSet.Post;
    end;
  finally
    DataSet.EnableControls;
  end;
end;

class function TTableJson.DataSetToJson(DataSet:TDataSet):string;
var
  sj, aj, sj2: ISuperObject;
  i: Integer;
  FieldType: string;
begin
  //����JSON����
  sj := SO();
  //�������������ַ�ʽ��һ���� TSuperObject.Create(stArray)������һ�����ýӿڷ�ʽ SA([]);
  aj := SA([]);
  try
    for i := 0 to DataSet.FieldCount - 1 do
    begin
      FieldType := GetEnumName(TypeInfo(TFieldType),ord(DataSet.Fields[i].DataType));
      Delete(FieldType,1,2);

      sj2 := SO(); //�����е���Ϣ����������Ӷ���
      sj2.I[cstFieldIndex] := DataSet.Fields[i].Index;
      sj2.S[cstFieldName]  := DataSet.Fields[i].FieldName;
      sj2.S[cstFieldType]  := FieldType;
      sj2.I[cstFieldSize]  := DataSet.Fields[i].Size;
      sj2.B[cstRequired]   := DataSet.Fields[i].Required;
      aj.AsArray.Add(sj2); //����ת����������AsArray
    end;
    sj.O[cstCols] := aj; //�������JSON����JSON���������O������֧�ָ�ֵ

    //�������ݼ�������

    DataSet.DisableControls;
    DataSet.First;
    aj := SA([]);
    while not DataSet.Eof do
    begin
      sj2 := SO();
      for i := 0 to DataSet.FieldCount - 1 do
      begin
        if VarIsNull(DataSet.Fields[i].Value) then
          sj2.O[DataSet.Fields[i].FieldName] := SO(Null)
        else
        begin
          CreateJsonValueByField(sj2,DataSet.Fields[i]);
        end;
      end;
      aj.AsArray.Add(sj2);
      DataSet.Next;
    end;
    sj.O[cstData] := aj;
    Result := sj.AsString;
  finally
    DataSet.EnableControls;
  end;
end;

end.