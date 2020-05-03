	<Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
		<PropertyGroup>
			<ProjectGuid>{DADA5C69-5401-4C18-839A-4258873B959E}</ProjectGuid>
			<ProjectVersion>13.4</ProjectVersion>
			<FrameworkType>FMX</FrameworkType>
			<MainSource>FMXClient.cpp</MainSource>
			<Base>True</Base>
			<Config Condition="'$(Config)'==''">Debug</Config>
			<Platform Condition="'$(Platform)'==''">OSX32</Platform>
			<TargetedPlatforms>5</TargetedPlatforms>
			<AppType>Application</AppType>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Config)'=='Base' or '$(Base)'!=''">
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="('$(Platform)'=='OSX32' and '$(Base)'=='true') or '$(Base_OSX32)'!=''">
			<Base_OSX32>true</Base_OSX32>
			<CfgParent>Base</CfgParent>
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="('$(Platform)'=='Win32' and '$(Base)'=='true') or '$(Base_Win32)'!=''">
			<Base_Win32>true</Base_Win32>
			<CfgParent>Base</CfgParent>
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Config)'=='Debug' or '$(Cfg_1)'!=''">
			<Cfg_1>true</Cfg_1>
			<CfgParent>Base</CfgParent>
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="('$(Platform)'=='OSX32' and '$(Cfg_1)'=='true') or '$(Cfg_1_OSX32)'!=''">
			<Cfg_1_OSX32>true</Cfg_1_OSX32>
			<CfgParent>Cfg_1</CfgParent>
			<Cfg_1>true</Cfg_1>
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="('$(Platform)'=='Win32' and '$(Cfg_1)'=='true') or '$(Cfg_1_Win32)'!=''">
			<Cfg_1_Win32>true</Cfg_1_Win32>
			<CfgParent>Cfg_1</CfgParent>
			<Cfg_1>true</Cfg_1>
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Config)'=='Release' or '$(Cfg_2)'!=''">
			<Cfg_2>true</Cfg_2>
			<CfgParent>Base</CfgParent>
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="('$(Platform)'=='OSX32' and '$(Cfg_2)'=='true') or '$(Cfg_2_OSX32)'!=''">
			<Cfg_2_OSX32>true</Cfg_2_OSX32>
			<CfgParent>Cfg_2</CfgParent>
			<Cfg_2>true</Cfg_2>
			<Base>true</Base>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Base)'!=''">
			<VerInfo_Keys>CompanyName=;FileDescription=;FileVersion=1.0.0.0;InternalName=;LegalCopyright=;LegalTrademarks=;OriginalFilename=;ProductName=;ProductVersion=1.0.0.0</VerInfo_Keys>
			<Manifest_File>None</Manifest_File>
			<VerInfo_Locale>2052</VerInfo_Locale>
			<ProjectType>FmxGuiApplication</ProjectType>
			<PackageImports>DataSnapIndy10ServerTransport;bindcompfmx;fmx;rtl;dbrtl;IndySystem;DbxClientDriver;bindcomp;inetdb;DBXInterBaseDriver;DataSnapCommon;DataSnapClient;DataSnapServer;DataSnapProviderClient;xmlrtl;DbxCommonDriver;IndyProtocols;DBXMySQLDriver;dbxcds;soaprtl;bindengine;DBXOracleDriver;CustomIPTransport;dsnap;DBXInformixDriver;fmxase;IndyCore;DBXFirebirdDriver;inet;fmxobj;inetdbxpress;DBXSybaseASADriver;fmxdae;IPIndyImpl;dbexpress;$(PackageImports)</PackageImports>
			<UsingDelphiRTL>true</UsingDelphiRTL>
			<DCC_Namespace>System;Xml;Data;Datasnap;Web;Soap;$(DCC_Namespace)</DCC_Namespace>
			<Icon_MainIcon>$(BDS)\bin\cbuilder_PROJECTICON.ico</Icon_MainIcon>
			<_TCHARMapping>wchar_t</_TCHARMapping>
			<AllPackageLibs>rtl.lib;fmx.lib;dbrtl.lib;DbxCommonDriver.lib;dsnap.lib;DataSnapCommon.lib;DbxClientDriver.lib;CustomIPTransport.lib;dbexpress.lib;IPIndyImpl.lib;IndySystem.lib;IndyProtocols.lib;IndyCore.lib;DataSnapServer.lib;inet.lib</AllPackageLibs>
			<DCC_CBuilderOutput>JPHNE</DCC_CBuilderOutput>
			<DynamicRTL>true</DynamicRTL>
			<IntermediateOutputDir>.\$(Platform)\$(Config)</IntermediateOutputDir>
			<FinalOutputDir>.\$(Platform)\$(Config)</FinalOutputDir>
			<BCC_wpar>false</BCC_wpar>
			<BCC_OptimizeForSpeed>true</BCC_OptimizeForSpeed>
			<BCC_ExtendedErrorInfo>true</BCC_ExtendedErrorInfo>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Base_OSX32)'!=''">
			<Manifest_File>$(BDS)\bin\default_app.manifest</Manifest_File>
			<UsingDelphiRTL>false</UsingDelphiRTL>
			<DynamicRTL>false</DynamicRTL>
			<Debugger_Launcher>/usr/X11/bin/xterm -e &quot;%debuggee%&quot;</Debugger_Launcher>
			<IncludePath>$(BDSINCLUDE)\osx\fmx;$(IncludePath)</IncludePath>
			<VerInfo_IncludeVerInfo>true</VerInfo_IncludeVerInfo>
			<VerInfo_Keys>CFBundleName=$(MSBuildProjectName);CFBundleDisplayName=$(MSBuildProjectName);CFBundleIdentifier=$(MSBuildProjectName);CFBundleVersion=1.0.0.0;CFBundlePackageType=APPL;CFBundleSignature=????;CFBundleAllowMixedLocalizations=YES;CFBundleExecutable=$(MSBuildProjectName)</VerInfo_Keys>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Base_Win32)'!=''">
			<PackageImports>fsADO16;frxDBX16;vcldbx;frx16;TeeDB;frxTee16;vclib;inetdbbde;Tee;DBXOdbcDriver;frxBDE16;baseComXE2;Rave100VCL;DBXSybaseASEDriver;ibxpress;fsIBX16;vclimg;fsBDE16;intrawebdb_120_160;frxDB16;ChartXE2;fs16;vclactnband;FMXTee;TeeUI;vcldsnap;bindcompvcl;vcldb;frxcs16;vclie;vcltouch;Intraweb_120_160;DBXDb2Driver;bcbsmp;websnap;frxADO16;vclribbon;VclSmp;fsDB16;frxe16;vcl;DataSnapConnectors;RptXE2;CloudService;DBXMSSQLDriver;CodeSiteExpressPkg;FmxTeeUI;dsnapcon;dclfrxTee16;fsTee16;vclx;webdsnap;bdertl;frxIBX16;adortl;bcbie;$(PackageImports)</PackageImports>
			<DCC_Namespace>Winapi;System.Win;Data.Win;Datasnap.Win;Web.Win;Soap.Win;Xml.Win;Bde;$(DCC_Namespace)</DCC_Namespace>
			<IncludePath>$(BDSINCLUDE)\windows\fmx;$(IncludePath)</IncludePath>
			<VerInfo_IncludeVerInfo>true</VerInfo_IncludeVerInfo>
			<VerInfo_Locale>1033</VerInfo_Locale>
			<Manifest_File>$(BDS)\bin\default_app.manifest</Manifest_File>
			<VerInfo_Keys>CompanyName=;FileDescription=;FileVersion=1.0.0.0;InternalName=;LegalCopyright=;LegalTrademarks=;OriginalFilename=;ProductName=;ProductVersion=1.0.0.0;Comments=</VerInfo_Keys>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Cfg_1)'!=''">
			<BCC_OptimizeForSpeed>false</BCC_OptimizeForSpeed>
			<BCC_DisableOptimizations>true</BCC_DisableOptimizations>
			<DCC_Optimize>false</DCC_Optimize>
			<DCC_DebugInfoInExe>true</DCC_DebugInfoInExe>
			<Defines>_DEBUG;$(Defines)</Defines>
			<BCC_InlineFunctionExpansion>false</BCC_InlineFunctionExpansion>
			<BCC_UseRegisterVariables>None</BCC_UseRegisterVariables>
			<DCC_Define>DEBUG</DCC_Define>
			<BCC_DebugLineNumbers>true</BCC_DebugLineNumbers>
			<TASM_DisplaySourceLines>true</TASM_DisplaySourceLines>
			<BCC_StackFrames>true</BCC_StackFrames>
			<ILINK_FullDebugInfo>true</ILINK_FullDebugInfo>
			<TASM_Debugging>Full</TASM_Debugging>
			<BCC_SourceDebuggingOn>true</BCC_SourceDebuggingOn>
			<ILINK_LibraryPath>$(BDSLIB)\$(PLATFORM)\debug;$(ILINK_LibraryPath)</ILINK_LibraryPath>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Cfg_1_OSX32)'!=''">
			<Debugger_DebugSourcePath>D:\Embarcadero\RAD Studio\9.0\source\fmx\;$(Debugger_DebugSourcePath)</Debugger_DebugSourcePath>
			<LinkPackageStatics>rtl.lib;fmx.lib;dbrtl.lib;DbxCommonDriver.lib;dsnap.lib;DataSnapCommon.lib;DbxClientDriver.lib;CustomIPTransport.lib;dbexpress.lib;IPIndyImpl.lib;IndySystem.lib;IndyProtocols.lib;IndyCore.lib;DataSnapServer.lib;inet.lib</LinkPackageStatics>
			<DCC_RemoteDebug>true</DCC_RemoteDebug>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Cfg_1_Win32)'!=''">
			<LinkPackageStatics>rtl.lib;fmx.lib;dbrtl.lib;DbxCommonDriver.lib;dsnap.lib;DataSnapCommon.lib;DbxClientDriver.lib;CustomIPTransport.lib;dbexpress.lib;IPIndyImpl.lib;IndySystem.lib;IndyProtocols.lib;IndyCore.lib;DataSnapServer.lib;inet.lib</LinkPackageStatics>
			<VerInfo_IncludeVerInfo>true</VerInfo_IncludeVerInfo>
			<VerInfo_Locale>1033</VerInfo_Locale>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Cfg_2)'!=''">
			<Defines>NDEBUG;$(Defines)</Defines>
			<TASM_Debugging>None</TASM_Debugging>
		</PropertyGroup>
		<PropertyGroup Condition="'$(Cfg_2_OSX32)'!=''">
			<DCC_RemoteDebug>true</DCC_RemoteDebug>
		</PropertyGroup>
		<ItemGroup>
			<CppCompile Include="About.cpp">
				<Form>frmAbout</Form>
				<DependentOn>About.h</DependentOn>
				<BuildOrder>3</BuildOrder>
			</CppCompile>
			<CppCompile Include="CallbackClient.cpp">
				<DependentOn>CallbackClient.h</DependentOn>
				<BuildOrder>5</BuildOrder>
			</CppCompile>
			<CppCompile Include="ClientBroker.cpp">
				<DependentOn>ClientBroker.h</DependentOn>
				<BuildOrder>6</BuildOrder>
			</CppCompile>
			<CppCompile Include="CZDataSet.cpp">
				<DependentOn>CZDataSet.h</DependentOn>
				<BuildOrder>7</BuildOrder>
			</CppCompile>
			<CppCompile Include="DSClientProxy.cpp">
				<DependentOn>DSClientProxy.h</DependentOn>
				<BuildOrder>13</BuildOrder>
			</CppCompile>
			<CppCompile Include="FMXClient.cpp">
				<BuildOrder>0</BuildOrder>
			</CppCompile>
			<CppCompile Include="fsScreenCursor.cpp">
				<DependentOn>fsScreenCursor.h</DependentOn>
				<BuildOrder>9</BuildOrder>
			</CppCompile>
			<CppCompile Include="Login.cpp">
				<Form>frmLogin</Form>
				<DependentOn>Login.h</DependentOn>
				<BuildOrder>2</BuildOrder>
			</CppCompile>
			<CppCompile Include="main.cpp">
				<Form>frmMain</Form>
				<DependentOn>main.h</DependentOn>
				<BuildOrder>1</BuildOrder>
			</CppCompile>
			<CppCompile Include="MsgStream.cpp">
				<DependentOn>MsgStream.h</DependentOn>
				<BuildOrder>8</BuildOrder>
			</CppCompile>
			<CppCompile Include="QQMain.cpp">
				<Form>frmQQMain</Form>
				<DependentOn>QQMain.h</DependentOn>
				<BuildOrder>10</BuildOrder>
			</CppCompile>
			<CppCompile Include="QQMessage.cpp">
				<Form>frmQQMessage</Form>
				<DependentOn>QQMessage.h</DependentOn>
				<BuildOrder>11</BuildOrder>
			</CppCompile>
			<FormResources Include="main.fmx"/>
			<FormResources Include="Login.fmx"/>
			<FormResources Include="QQMessage.fmx"/>
			<FormResources Include="QQMain.fmx"/>
			<FormResources Include="About.fmx"/>
			<BuildConfiguration Include="Release">
				<Key>Cfg_2</Key>
				<CfgParent>Base</CfgParent>
			</BuildConfiguration>
			<BuildConfiguration Include="Base">
				<Key>Base</Key>
			</BuildConfiguration>
			<BuildConfiguration Include="Debug">
				<Key>Cfg_1</Key>
				<CfgParent>Base</CfgParent>
			</BuildConfiguration>
		</ItemGroup>
		<ProjectExtensions>
			<Borland.Personality>CPlusPlusBuilder.Personality.12</Borland.Personality>
			<Borland.ProjectType>FmxGuiApplication</Borland.ProjectType>
			<BorlandProject>
				<CPlusPlusBuilder.Personality>
					<Source>
						<Source Name="MainSource">FMXClient.cpp</Source>
					</Source>
					<VersionInfo>
						<VersionInfo Name="IncludeVerInfo">False</VersionInfo>
						<VersionInfo Name="AutoIncBuild">False</VersionInfo>
						<VersionInfo Name="MajorVer">1</VersionInfo>
						<VersionInfo Name="MinorVer">0</VersionInfo>
						<VersionInfo Name="Release">0</VersionInfo>
						<VersionInfo Name="Build">0</VersionInfo>
						<VersionInfo Name="Debug">False</VersionInfo>
						<VersionInfo Name="PreRelease">False</VersionInfo>
						<VersionInfo Name="Special">False</VersionInfo>
						<VersionInfo Name="Private">False</VersionInfo>
						<VersionInfo Name="DLL">False</VersionInfo>
						<VersionInfo Name="Locale">2052</VersionInfo>
						<VersionInfo Name="CodePage">936</VersionInfo>
					</VersionInfo>
					<VersionInfoKeys>
						<VersionInfoKeys Name="CompanyName"/>
						<VersionInfoKeys Name="FileDescription"/>
						<VersionInfoKeys Name="FileVersion">1.0.0.0</VersionInfoKeys>
						<VersionInfoKeys Name="InternalName"/>
						<VersionInfoKeys Name="LegalCopyright"/>
						<VersionInfoKeys Name="LegalTrademarks"/>
						<VersionInfoKeys Name="OriginalFilename"/>
						<VersionInfoKeys Name="ProductName"/>
						<VersionInfoKeys Name="ProductVersion">1.0.0.0</VersionInfoKeys>
						<VersionInfoKeys Name="Comments"/>
					</VersionInfoKeys>
					<Excluded_Packages>
						<Excluded_Packages Name="$(BDSBIN)\bcboffice2k160.bpl">Embarcadero C++Builder Office 2000 Servers Package</Excluded_Packages>
						<Excluded_Packages Name="$(BDSBIN)\bcbofficexp160.bpl">Embarcadero C++Builder Office XP Servers Package</Excluded_Packages>
						<Excluded_Packages Name="$(BDSBIN)\dcloffice2k160.bpl">Microsoft Office 2000 Sample Automation Server Wrapper Components</Excluded_Packages>
						<Excluded_Packages Name="$(BDSBIN)\dclofficexp160.bpl">Microsoft Office XP Sample Automation Server Wrapper Components</Excluded_Packages>
					</Excluded_Packages>
					<ProjectProperties>
						<ProjectProperties Name="AutoShowDeps">False</ProjectProperties>
						<ProjectProperties Name="ManagePaths">True</ProjectProperties>
						<ProjectProperties Name="VerifyPackages">True</ProjectProperties>
					</ProjectProperties>
				</CPlusPlusBuilder.Personality>
				<Deployment>
					<DeployFile Class="ProjectOSXInfoPList" Configuration="Debug" LocalName=".\OSX32\Debug\FMXClient.info.plist">
						<Platform Name="OSX32">
							<RemoteName>Info.plist</RemoteName>
						</Platform>
					</DeployFile>
					<DeployFile Class="DependencyModule" Condition="'$(UsingDelphiRTL)'=='true'" LocalName="$(BDS)\bin\borlndmm.dll">
						<Platform Name="Win32"/>
					</DeployFile>
					<DeployFile Class="DebugSymbols" Configuration="Debug" LocalName=".\OSX32\Debug\FMXClient.tds">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS\</RemoteDir>
							<RemoteName>FMXClient.tds</RemoteName>
						</Platform>
					</DeployFile>
					<DeployFile Class="ProjectOSXResource" Configuration="Debug" LocalName=".\OSX32\Debug\FMXClient.icns">
						<Platform Name="OSX32"/>
					</DeployFile>
					<DeployFile Class="ProjectOutput" Configuration="Debug" LocalName=".\OSX32\Debug\FMXClient">
						<Platform Name="OSX32"/>
					</DeployFile>
					<DeployFile Class="DependencyModule" Condition="'$(DynamicRTL)'=='true'" LocalName="$(BDS)\Redist\osx32\libcgstl.dylib">
						<Platform Name="OSX32"/>
					</DeployFile>
					<DeployFile Class="ProjectOutput" Configuration="Debug" LocalName=".\Win32\Debug\FMXClient.exe">
						<Platform Name="Win32"/>
					</DeployFile>
					<DeployFile Class="DependencyModule" Condition="'$(DynamicRTL)'=='true' And '$(Multithreaded)'!='true'" LocalName="$(BDS)\bin\cc32120.dll">
						<Platform Name="Win32"/>
					</DeployFile>
					<DeployFile Class="DependencyModule" Condition="'$(DynamicRTL)'=='true' And '$(Multithreaded)'=='true'" LocalName="$(BDS)\bin\cc32120mt.dll">
						<Platform Name="Win32"/>
					</DeployFile>
					<DeployFile Class="DependencyModule" Condition="'$(DynamicRTL)'=='true'" LocalName="$(BDS)\Redist\osx32\libcgcrtl.dylib">
						<Platform Name="OSX32"/>
					</DeployFile>
					<DeployFile Class="DependencyModule" LocalName="$(BDS)\Redist\osx32\libcgunwind.1.0.dylib">
						<Platform Name="OSX32"/>
					</DeployFile>
					<DeployFile Class="DebugSymbols" Configuration="Debug" LocalName=".\Win32\Debug\FMXClient.tds">
						<Platform Name="Win32">
							<RemoteName>FMXClient.tds</RemoteName>
						</Platform>
					</DeployFile>
					<DeployFile Class="File" LocalName="D:\Embarcadero\RAD Studio\9.0\binosx32\libmidas.dylib">
						<Platform Name="OSX32">
							<RemoteName>libmidas.dylib</RemoteName>
						</Platform>
						<Platform Name="Win32">
							<RemoteName>libmidas.dylib</RemoteName>
						</Platform>
					</DeployFile>
					<DeployClass Name="ProjectOutput" Required="true">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS</RemoteDir>
							<Operation>1</Operation>
						</Platform>
						<Platform Name="Win32">
							<Operation>0</Operation>
						</Platform>
					</DeployClass>
					<DeployClass Name="DependencyPackage" Required="true">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS</RemoteDir>
							<Operation>1</Operation>
							<Extensions>.dylib</Extensions>
						</Platform>
						<Platform Name="Win32">
							<Operation>0</Operation>
							<Extensions>.bpl</Extensions>
						</Platform>
					</DeployClass>
					<DeployClass Name="DependencyModule">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS</RemoteDir>
							<Operation>1</Operation>
							<Extensions>.dylib</Extensions>
						</Platform>
						<Platform Name="Win32">
							<Operation>0</Operation>
							<Extensions>.dll;.bpl</Extensions>
						</Platform>
					</DeployClass>
					<DeployClass Name="ProjectOSXInfoPList">
						<Platform Name="OSX32">
							<RemoteDir>Contents</RemoteDir>
							<Operation>1</Operation>
						</Platform>
					</DeployClass>
					<DeployClass Name="File">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS</RemoteDir>
							<Operation>0</Operation>
						</Platform>
						<Platform Name="Win32">
							<Operation>0</Operation>
						</Platform>
					</DeployClass>
					<DeployClass Name="DebugSymbols">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS</RemoteDir>
							<Operation>1</Operation>
						</Platform>
						<Platform Name="Win32">
							<Operation>0</Operation>
						</Platform>
					</DeployClass>
					<DeployClass Name="DependencyFramework">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS</RemoteDir>
							<Operation>1</Operation>
							<Extensions>.framework</Extensions>
						</Platform>
						<Platform Name="Win32">
							<Operation>0</Operation>
						</Platform>
					</DeployClass>
					<DeployClass Name="AdditionalDebugSymbols">
						<Platform Name="OSX32">
							<RemoteDir>Contents\MacOS</RemoteDir>
							<Operation>1</Operation>
						</Platform>
						<Platform Name="Win32">
							<Operation>0</Operation>
						</Platform>
					</DeployClass>
					<DeployClass Name="ProjectOSXResource">
						<Platform Name="OSX32">
							<RemoteDir>Contents\Resources</RemoteDir>
							<Operation>1</Operation>
						</Platform>
					</DeployClass>
					<ProjectRoot Name="$(PROJECTNAME).app" Platform="OSX32"/>
					<ProjectRoot Name="$(PROJECTNAME)" Platform="Win64"/>
					<ProjectRoot Name="$(PROJECTNAME)" Platform="Win32"/>
				</Deployment>
				<Platforms>
					<Platform value="OSX32">True</Platform>
					<Platform value="Win32">True</Platform>
				</Platforms>
				<ModelSupport>False</ModelSupport>
				<DataSnapProxyLookup>
					<DSClientProxy>{F1016E56-39E7-4E75-AFBD-0E7B04AED31B}</DSClientProxy>
				</DataSnapProxyLookup>
			</BorlandProject>
			<ProjectFileVersion>12</ProjectFileVersion>
		</ProjectExtensions>
		<Import Condition="Exists('$(BDS)\Bin\CodeGear.Cpp.Targets')" Project="$(BDS)\Bin\CodeGear.Cpp.Targets"/>
		<Import Condition="Exists('$(APPDATA)\Embarcadero\$(BDSAPPDATABASEDIR)\$(PRODUCTVERSION)\UserTools.proj')" Project="$(APPDATA)\Embarcadero\$(BDSAPPDATABASEDIR)\$(PRODUCTVERSION)\UserTools.proj"/>
		<Import Condition="Exists('$(MSBuildProjectName).deployproj')" Project="$(MSBuildProjectName).deployproj"/>
	</Project>
