using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;


public class CineX : ModuleRules
{
    private string[] allModules = new string[]
    {
        "zmq",
        "sodium",
        "turbojpeg",
        "NvidiaCapture",
    };

    private Dictionary<string, string> moduleDllConfigs = new Dictionary<string, string>()
    {
        {  "zmq", "libzmq-v140-mt-4_2_1.dll" },
        {  "sodium", "libsodium.dll" },
        {  "turbojpeg", "jpeg8.dll" },
    };

    private Dictionary<string, string> moduleLibConfigs = new Dictionary<string, string>()
    {
        {  "zmq", "libzmq-v140-mt-4_2_1.lib" },
        {  "turbojpeg", "jpeg.lib" },
        {  "NvidiaCapture", "nvapi64.lib" },
    };

    private string[] CineXModuleDepends = new string[] {
        "zmq", "sodium", "turbojpeg", "NvidiaCapture"
    };
    private string CommonRoot
    {
        get { return Path.Combine(UEPluginRoot, "ThirdParty"); }
    }
    private string CommonInc
    {
        get { return CommonRoot; }
    }
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }
    private string PluginModule
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../..")); }
    }
    private string UEPluginRoot
    {
        get { return Path.GetFullPath(Path.Combine(PluginModule, "..")); }
    }
    private string ProjectPath
    {
        get { return Path.GetFullPath(Path.Combine(UEPluginRoot, "..")); }
    }
    private string CineXSDKRoot
    {
        get { return Path.Combine(CommonRoot, "CineXSDK"); }
    }
    private string BinaryPath
    {
        get { return Path.Combine(ProjectPath, "Binaries/Win64"); }
    }
    private List<string> CineXSDKLibs
    {
        get { return CineXSdkDeps; }
    }
    private List<string> CineXSdkDeps = new List<string>();
    private void CopyIfNewer(string srcPath, string destDir)
    {
        FileInfo file = new FileInfo(srcPath);
        FileInfo destFile = new FileInfo(Path.Combine(destDir, file.Name));
        if (!destFile.Directory.Exists)
        {
            destFile.Directory.Create();
        }

        if (!destFile.Exists || file.LastWriteTime > destFile.LastWriteTime)
        {
            // now you can safely overwrite it
            file.CopyTo(destFile.FullName, true);
        }
        return;
    }


    private void loadCineXSDKDependencies(bool addCineXMacro, string prefix)
    {
        foreach (var module in CineXModuleDepends)
        {
            var IncDir = Path.Combine(CineXSDKRoot, "include", module);
            if (System.IO.Directory.Exists(IncDir))
            {
                PrivateIncludePaths.Add(IncDir);
            }

            if (moduleLibConfigs.ContainsKey(module))
            {
                PublicAdditionalLibraries.Add(Path.Combine(CineXSDKRoot, "lib", moduleLibConfigs[module]));
            }

            if (moduleDllConfigs.ContainsKey(module))
            {
                var dllPath = Path.Combine(CineXSDKRoot, "bin", moduleDllConfigs[module]);
                PublicDelayLoadDLLs.Add(dllPath);
                CineXSDKLibs.Add(moduleDllConfigs[module]);
                CopyIfNewer(dllPath, BinaryPath);
            }
        }
        #region predefine_macro
        if (addCineXMacro)
        {
            var CineXSDKLibsMacro = string.Join(",", CineXSDKLibs);
            var CineXSDKPassMacro = string.Format("{0}_CineX_SDK_LIBS=\"{1}\"", prefix, CineXSDKLibsMacro);

            System.Console.WriteLine(CineXSDKPassMacro);
            Definitions.Add(CineXSDKPassMacro);
        }
        #endregion
    }

    private void loadCineXSDKDependencies()
    {
        loadCineXSDKDependencies(false, null);
    }





	public CineX(ReadOnlyTargetRules Target) : base(Target)
	{
        // Standard Module Dependencies
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {
            "Engine", "Core", "CoreUObject", "InputCore", "SequenceRecorder",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
            "RenderCore",
            "UnrealEd",
            "PropertyEditor",
            "LevelEditor",
            "CinematicCamera",
			"Sequencer",
			"LevelSequence",
			"LevelSequenceEditor",
			"AssetRegistry",
            "RHI",
            "UMG",
            "Projects",
            "Slate",
            "SlateCore",
	        "Engine",
            "Core",
            "InputCore",
            "Networking",
            "Sockets",});

		PrivateIncludePaths.Add("Source/CineX/Private");
        PublicIncludePaths.Add("Source/CineX/Public");

        loadCineXSDKDependencies(true, "CineX");

        #region predefine_macro
        Definitions.Add("WITH_ZMQ_BINDING=1");
        #endregion
	}
}