# 设置用户名，密码，邮箱：

全局设置，一次就行
git config --global user.name "adce"
git config --global user.email "adce@qq.com"


# 查看邮箱和用户名

git config user.name

git config user.email


# 新建仓库

mkdir test
cd test
git init
touch README.md
git add README.md
git commit -m "first commit"
git remote add origin https://gitee.com/adce9/test.git
git push -u origin "master"

已有仓库

cd existing_git_repo
git remote add origin https://gitee.com/adce9/test.git
git push -u origin "master"

# git回滚

git reflog 查看回滚的版本

git reset --hard 93c7150 回滚到具体的版本号

# vscode发布到GitHub超时，使用全局代理

```
git config --global https.proxy [http://127.0.0.1:1080](http://127.0.0.1:1080/)
 
git config --global https.proxy [https://127.0.0.1:1080](https://127.0.0.1:1080/)
```

# 取消代理

git config --global --unset http.proxy

git config --global --unset https.proxy
