
﻿C++/Additional Include Directories => $(ProjectDir)src;%(AdditionalIncludeDirectories)

C++/Additional Include Directories => $(ProjectDir)src;%(AdditionalIncludeDirectories)

Configuration Prop/C++ Language standard => Cpp20
Linker/System/subsystem => windows
C++/General/Multiprossor compilation => Yes(/MP)
C++/General/WarningLevel => L4
Configuration Properties/General/ output directory => $(SolutionDir)bin\$(Configuration)\
Linker/General/ Enable Incremental Linking => Yes
Configuration Properties/ Advance => Unicode G
Intermediate Directory => $(SolutionDir)build\intermediate\$(ProjectName)\$(Platform)\$(Configuration)\
Output Directory => $(SolutionDir)build\bin\$(Platform)\$(Configuration)\


// Visual studio configuration for the vulkan
C/C++ → General → Additional Include Directories
    $(VULKAN_SDK)\Include

Linker → General → Additional Library Directories (x64)
    $(VULKAN_SDK)\Lib

Linker → General → Additional Library Directories (Win32)
    $(VULKAN_SDK)\Lib32

Linker → Input → Additional Dependencies
    vulkan-1.lib