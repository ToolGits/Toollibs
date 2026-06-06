#ifndef TOOLLIBS_POP_PLUGIN_HPP
#define TOOLLIBS_POP_PLUGIN_HPP

namespace POP
{
    void Initialize();

    void GenerateGitKeeps(const char* rootPath);

    void GitAdd();

    void GitCommit();

    void GitPushPrompt();

    void Run();
}

#endif