##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SkypeChat
ConfigurationName      :=Debug
WorkspacePath          := "/home/Data/SkypeChat"
ProjectPath            := "/home/Data/SkypeChat/SkypeChat"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=andrian Yablonskyy
Date                   :=09.09.13
CodeLitePath           :="/home/TOROKI-WIND/andrian.yablonskyy/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="SkypeChat.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell wx-config --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)wxsqlite3-3.0.5/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)wxsqlite3-2.8 
ArLibs                 :=  "wxsqlite3-2.8" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)wxsqlite3-3.0.5/lib 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes ) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes ) $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/SkypeChatMainFrame$(ObjectSuffix) $(IntermediateDirectory)/ClassPrototypes$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Data/SkypeChat/SkypeChat/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/SkypeChatMainFrame$(ObjectSuffix): SkypeChatMainFrame.cpp $(IntermediateDirectory)/SkypeChatMainFrame$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Data/SkypeChat/SkypeChat/SkypeChatMainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SkypeChatMainFrame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SkypeChatMainFrame$(DependSuffix): SkypeChatMainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SkypeChatMainFrame$(ObjectSuffix) -MF$(IntermediateDirectory)/SkypeChatMainFrame$(DependSuffix) -MM "SkypeChatMainFrame.cpp"

$(IntermediateDirectory)/SkypeChatMainFrame$(PreprocessSuffix): SkypeChatMainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SkypeChatMainFrame$(PreprocessSuffix) "SkypeChatMainFrame.cpp"

$(IntermediateDirectory)/ClassPrototypes$(ObjectSuffix): ClassPrototypes.cpp $(IntermediateDirectory)/ClassPrototypes$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Data/SkypeChat/SkypeChat/ClassPrototypes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ClassPrototypes$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ClassPrototypes$(DependSuffix): ClassPrototypes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ClassPrototypes$(ObjectSuffix) -MF$(IntermediateDirectory)/ClassPrototypes$(DependSuffix) -MM "ClassPrototypes.cpp"

$(IntermediateDirectory)/ClassPrototypes$(PreprocessSuffix): ClassPrototypes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ClassPrototypes$(PreprocessSuffix) "ClassPrototypes.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/SkypeChatMainFrame$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SkypeChatMainFrame$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SkypeChatMainFrame$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ClassPrototypes$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ClassPrototypes$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ClassPrototypes$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/SkypeChat"


