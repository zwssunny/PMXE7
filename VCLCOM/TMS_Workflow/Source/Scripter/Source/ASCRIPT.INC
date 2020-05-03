{$RANGECHECKS OFF}
{$BOOLEVAL OFF}

{Set directive THEMED_IDE to use additional TMS Components in the scripter IDE. The IDE will be themed, you will be
 able to set an AppStyler to the TIDEDialog component}
{.$DEFINE THEMED_IDE}

{.$DEFINE OverrideDescendants}
{Until version 2.6.3.0 of Scripter Studio, the method/properties registration system worked this way:
 Whenever a method/property was registered in a class, it was also registered in all descendants of the class,
 regardless if the method was already registered or not. For example, let's say Create method was registered
 in TComponent class, receiving 1 parameter:

 DefineClass(TComponent).DefineMethod('Create', 1, .....);

 then the same Create method is declared in TObject class, but receiving 0 parameter:

 DefineClass(TObject).DefineMethod('Create', 0, .....);

 the last create method would override the first one declared in TComponent class. This way, the Create method
 of TComponent would accept no parameters.

 This of course was wrong, and then fixed: if a method is already declared in a descendant, it will not be overriden.

 However, since this changes the registration system very deeply, and since lots of user are registering lots
 of classes and methods, maybe this bug fix might break working code. Thus, the directive OverrideDescendants
 can be defined in order to use the old (buggy) mechanism, to keep old code working, if necessary}


{Define UseGreatisUnits directive to use scripter pro together with greatis components}
{.$DEFINE UseGreatisUnits}

// Do not change anything below this line
//------------------------------------------------------------------------------
{$IFNDEF BCB}
{$DEFINE ISDELPHI}
{$ENDIF}

{$IF CompilerVersion >= 24}
  {$LEGACYIFEND ON}
{$IFEND}

{$DEFINE DELPHI2_LVL}
{$DEFINE DELPHI3_LVL}
{$DEFINE DELPHI4_LVL}
{$DEFINE DELPHI5_LVL}
{$DEFINE DELPHI6_LVL}
{$DEFINE DELPHI7_LVL}

{$IF CompilerVersion >= 17}
  {$DEFINE DELPHI9_LVL}
{$IFEND}

{$IF CompilerVersion >= 18}
  {$DEFINE DELPHI2006_LVL}
{$IFEND}

{$IF CompilerVersion >= 19}
  {$DEFINE DELPHI2007_LVL}
{$IFEND}

{$IF CompilerVersion >= 20}
  {$DEFINE DELPHI2009_LVL}
{$IFEND}

{$IF CompilerVersion >= 21}
  {$DEFINE DELPHI2010_LVL}
{$IFEND}

{$IF CompilerVersion >= 22}
  {$DEFINE DELPHI2011_LVL}
  {$DEFINE DELPHIXE_LVL}
{$IFEND}

{$IF CompilerVersion >= 23}
  {$DEFINE DELPHI2012_LVL}
  {$DEFINE DELPHIXE2_LVL}
{$IFEND}

{$IF CompilerVersion >= 24}
  {$DEFINE DELPHIXE3_LVL}
{$IFEND}

{$IF CompilerVersion >= 25}
  {$DEFINE DELPHIXE4_LVL}
{$IFEND}

{$IF CompilerVersion >= 26}
  {$DEFINE DELPHIXE5_LVL}
{$IFEND}

{$IF CompilerVersion >= 28}
  {$DEFINE DELPHIXE7_LVL}
{$IFEND}

{$IFDEF DELPHI7_LVL}
{$WARN UNIT_PLATFORM OFF}
{$WARN SYMBOL_PLATFORM OFF}
{$ENDIF}

{$IFDEF NEXTGEN}
  {$ZEROBASEDSTRINGS OFF}
  {$DEFINE NEWSTACK}
{$ELSE}
{$ENDIF}

{$IFDEF CPUX64}
  {$DEFINE DLL_RTTI}
{$ENDIF}
