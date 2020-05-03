#ifndef PubEnumH
#define PubEnumH

enum TZComboBoxItemIndex
{
  cbItem1,
  cbItem2,
  cbItem3,
  cbItem4,
  cbItem5,
  cbItem6,
  cbItem7
};

enum TZCharType
{
  ctNormal,
  ctCharacter, //除数字以外的所有字符
  ctLetter,   //仅仅字母
  ctPlus,     //正整数
  ctNegative,  //负整数
  ctInteger,  //整数
  ctPlusFloat,      //正浮点数  和 0
  ctNegativeFloat,  //负浮点数  和 0
  ctFloat,          //浮点数
  ctID,             //第一个字母，以后字母,数字，"-"号
  ctSelfDefine   //自定义
};

enum TZCharCase
{
  ccNormal,
  ccUpperCase,
  ccLowerCase
};
enum TZCalculateType
{
 ctNone,
 ctSum,
 ctAvg,
 ctCount
};
#endif
