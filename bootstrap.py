import os
import subprocess


# 初始化设备

def init_dependency(github_url: str):
    name = github_url.split('/')[-1]
    if github_url.endswith('/'):
        github_url = github_url[:-1]
    if os.path.exists(name):
        print('name is ok, already exist')
        return
    # ok, do the logic
    repo_root_path = os.path.abspath('..')
    repo_path = os.path.join(repo_root_path, name)

    if not os.path.exists(repo_path):
        subprocess.run(['git', 'clone', github_url], cwd=repo_root_path)
    # ok, make the link
    print(repo_path)
    print(name)
    # New-Item -Path C:\LinkDir -ItemType SymbolicLink -Value F:\RealDir
    subprocess.run(['powershell', '-Command', f'New-Item -Path {repo_path} -ItemType SymbolicLink -Value {name}'])


init_dependency("https://github.com/huhuang03/QtAwesome")
