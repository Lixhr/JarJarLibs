#include "jjl.hpp"

int do_sys_command_stream(const std::string& cmd) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        throw std::runtime_error("pipe() failed");
    }

    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        throw std::runtime_error("fork() failed");
    }

    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execl("/bin/sh", "sh", "-c", cmd.c_str(), (char*)nullptr);
        throw std::runtime_error("Failed to execute " + cmd);
    }

    close(pipefd[1]);

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        throw std::runtime_error("waitpid() failed");
    }

    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        throw std::runtime_error("Command exited with non-zero status: " + cmd);
    }

    return (pipefd[0]);
}