//---------------------------------------------------------------------------
#include <set>
#ifndef DynamicGridH
#define DynamicGridH
//---------------------------------------------------------------------------
template < class T > class TDynamicGrid;
template < class T > class TDynamicGridRow;
template < class T > class TDynamicGridCell;
//---------------------------------------------------------------------------
template<class T>
struct TDynamicGridCompare : public std::binary_function<T, T, bool>
{
  bool operator() (const T& Key1, const T&Key2) const
  {
     if(Key1.GetIndex() < Key2.GetIndex())
        return true;
     else
        return false;
  }
};
//---------------------------------------------------------------------------
template < class T >
class TDynamicGrid
{
public:
    typedef typename TDynamicGridCell< T > Cell_Type;
    typedef typename TDynamicGridRow< T >  Row_Type;
private:
    typedef typename std::set< Row_Type, TDynamicGridCompare<Row_Type> > Rows_Type;
    std::set< Row_Type, TDynamicGridCompare<Row_Type> > FRows;
public:
    TDynamicGrid();
    ~TDynamicGrid();
    void Clear();
    void Erase(int Row);
    void Erase(int Row, int Col);
    int  RowCount();
    int  ColCount(int ARow);
    void ClearGarbage();

    bool Have(int Row, int Col) const;
    T&   Get(int Row, int Col);
    void Set(int Row, int Col, T&Value);
    Row_Type& GetRow(int Row);
};
//---------------------------------------------------------------------------
template < class T >
class TDynamicGridRow
{
public:
    typedef typename TDynamicGridCell< T > Cell_Type;
    typedef typename std::set< Cell_Type, TDynamicGridCompare< Cell_Type > > Cells_Type;
private:
    int FIndex;
    std::set< Cell_Type, TDynamicGridCompare< Cell_Type > > FCells;
public:
    TDynamicGridRow();
    ~TDynamicGridRow();
    int GetIndex() const;
    void SetIndex(int AIndex);

    int  ColCount();

    bool Have(int Col) const;
    T& Get(int Col);
    void Set(int Col, T&Value);
    void Erase(int Col);
};
//---------------------------------------------------------------------------
template < class T >
class TDynamicGridCell
{
    int FIndex;
public:
    TDynamicGridCell();
    ~TDynamicGridCell();
    int GetIndex() const;
    void SetIndex(int AIndex);
    T    Value;
};
//---------------------------------------------------------------------------
template < class T >
TDynamicGrid<T>::TDynamicGrid()
{
}
template < class T >
TDynamicGrid<T>::~TDynamicGrid()
{
}
template < class T >
bool TDynamicGrid<T>::Have(int Row, int Col) const
{
    static TDynamicGrid<T>::Row_Type TempRow;
    TempRow.SetIndex(Row);
    Rows_Type::const_iterator row_itr = FRows.find(TempRow);
    if(row_itr == FRows.end())
        return false;
    return row_itr->Have(Col);
}
template < class T >
T& TDynamicGrid<T>::Get(int Row, int Col)
{
    static TDynamicGrid<T>::Row_Type TempRow;
    static TDynamicGrid<T>::Cell_Type TempCell;
    TempRow.SetIndex(Row);
    Rows_Type::iterator row_itr = FRows.find(TempRow);
    if(row_itr == FRows.end())
    {
        TempCell.SetIndex(-1);
        return TempCell.Value;
    }
    return row_itr->Get(Col);
}
template < class T >
TDynamicGrid<T>::Row_Type& TDynamicGrid<T>::GetRow(int Row)
{
    static TDynamicGrid<T>::Row_Type TempRow;
    TempRow.SetIndex(Row);
    Rows_Type::iterator row_itr = FRows.find(TempRow);
    if(row_itr == FRows.end())
    {
        return TempRow;
    }
    return *row_itr;
}
template < class T >
void TDynamicGrid<T>::Set(int Row, int Col, T&AValue)
{
    static TDynamicGrid<T>::Row_Type TempRow;
    TempRow.SetIndex(Row);
    Rows_Type::iterator row_itr = FRows.find(TempRow);
    if(row_itr == FRows.end())
    {
        std::pair< Rows_Type::iterator, bool > result = FRows.insert(TempRow);
        if(result.second)
            row_itr = result.first;
        else
            throw Exception("TDynamicGrid insert row failed!");
    }
    row_itr->Set(Col, AValue);
}
template < class T >
void TDynamicGrid<T>::Erase(int Row, int Col)
{
    static TDynamicGrid<T>::Row_Type TempRow;
    TempRow.SetIndex(Row);
    Rows_Type::iterator row_itr = FRows.find(TempRow);
    if(row_itr == FRows.end())
    {
        return;
    }
    row_itr->Erase(Col);
}
template < class T >
void TDynamicGrid<T>::Erase(int Row)
{
    static TDynamicGrid<T>::Row_Type TempRow;
    TempRow.SetIndex(Row);
    Rows_Type::iterator row_itr = FRows.find(TempRow);
    if(row_itr == FRows.end())
    {
        return;
    }
    FRows.erase(row_itr);
}
template < class T >
void TDynamicGrid<T>::Clear()
{
    FRows.clear();
}
template < class T >
void TDynamicGrid<T>::ClearGarbage()
{
    for(Rows_Type::iterator row_itr = FRows.begin(); row_itr != FRows.end(); row_itr++)
    {
        if(row_itr->ColCount() == 0)
            FRows.erase(row_itr);
    }
}
template < class T >
int TDynamicGrid<T>::RowCount()
{
    return FRows.size();
}
template < class T >
int TDynamicGrid<T>::ColCount(int ARow)
{
    static TDynamicGrid<T>::Row_Type TempRow;
    TempRow.SetIndex(ARow);
    Rows_Type::iterator row_itr = FRows.find(TempRow);
    if(row_itr == FRows.end())
    {
        return 0;
    }
    return row_itr->ColCount();
}
//---------------------------------------------------------------------------
template < class T >
TDynamicGridRow<T>::TDynamicGridRow()
                   :FIndex(-1)
{
}
template < class T >
TDynamicGridRow<T>::~TDynamicGridRow()
{
}
template < class T >
int TDynamicGridRow<T>::GetIndex() const
{
   return FIndex;
}
template < class T >
void TDynamicGridRow<T>::SetIndex(int AIndex)
{
   FIndex = AIndex;
}
template < class T >
bool TDynamicGridRow<T>::Have(int Col) const
{
    static TDynamicGrid<T>::Cell_Type TempCell;
    TempCell.SetIndex(Col);
    Cells_Type::const_iterator cell_itr = FCells.find(TempCell);
    if(cell_itr != FCells.end())
        return true;
    return false;
}
template < class T >
T& TDynamicGridRow<T>::Get(int Col)
{
    static TDynamicGrid<T>::Cell_Type TempCell;
    TempCell.SetIndex(Col);
    Cells_Type::iterator cell_itr = FCells.find(TempCell);
    if(cell_itr != FCells.end())
        return cell_itr->Value;
    return TempCell.Value;
}
template < class T >
void TDynamicGridRow<T>::Set(int Col, T&AValue)
{
    static Cell_Type TempCell;
    TempCell.SetIndex(Col);
    Cells_Type::iterator cell_itr = FCells.find(TempCell);
    if(cell_itr == FCells.end())
    {
        std::pair< Cells_Type::iterator, bool > result = FCells.insert(TempCell);
        if(result.second)
            cell_itr = result.first;
        else
            throw Exception("TDynamicGrid insert cell failed!");
    }
    cell_itr->Value = AValue;
}
template < class T >
void TDynamicGridRow<T>::Erase(int Col)
{
    static TDynamicGrid<T>::Cell_Type TempCell;
    TempCell.SetIndex(Col);
    Cells_Type::iterator cell_itr = FCells.find(TempCell);
    if(cell_itr == FCells.end())
    {
        return;
    }
    FCells.erase(cell_itr);
}
template < class T >
int  TDynamicGridRow<T>::ColCount()
{
    return FCells.size();
}
//---------------------------------------------------------------------------
template < class T >
TDynamicGridCell<T>::TDynamicGridCell()
                    :FIndex(-1)
{
}
template < class T >
TDynamicGridCell<T>::~TDynamicGridCell()
{
}
template < class T >
int TDynamicGridCell<T>::GetIndex() const
{
   return FIndex;
}
template < class T >
void TDynamicGridCell<T>::SetIndex(int AIndex)
{
   FIndex = AIndex;
}
#endif
