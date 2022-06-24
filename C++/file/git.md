# git使用流程：

## 1.配置全局用户名和邮箱，标记本台主机

全局设置，一次就行：
git config --global user.name "adce"
git config --global user.email "adce@qq.com"

查看用户名和邮箱：
git config user.name
git config user.email

## 2.选择仓库，并初始化仓库

选择仓库：
mkdir mygit
cd mygit

初始化仓库：
git init

## 3.将文件添加到仓库（此时还没有提交到远程仓库，只是本地保存）

将文件保存在暂存区。

touch file.txt

添加到仓库：
git add file.txt

## 4.将已经添加到仓库的文件提交到仓库

提交到特定的分支，默认是master。
一般是多次add，一次commit。
commit只提交暂存区里的版本，没有进入暂存区的（也就是没有add的）不会被提交。

git commit -m "message you want to say."

## 5.如果文件中间 被修改

git add file.txt  // 添加修改的文件

git commit -m "second message."  // 再次提交

## 6.如果中间文件被删除

rm file.txt

1.从暂存区也把文件删除
git rm file.txt

2.删错了，从暂存区回退出来
git checkout -- file.txt

从来没有被添加到版本库就被删除的文件，是无法恢复的。

## 7.添加远程仓库源

git remote add origin https://github.com/adce-zcl/adce-test.git

git remote -v  // 查看远程仓库的信息

git remote rm origin // 删除指定的远程仓库

## 8.推送到远程仓库

git push -u origin master // 将master分支推送到origin仓库

只有第一次需要 -u 参数，可以把远程仓库和本地仓库关联起来，后续的提交只要：

git push origin master

## 9.推送失败，有冲突，先pull下来，再推送

git pull  // 拉去与当前分支关联的远程仓库的对应分支
git branch --set-upstream-to=origin/dev dev	// 关联本地分支和远程仓库分支

手动解决冲突后，再push即可。


# 通用命令

## 查看git状态

git status

## 查看文件具体的差异

git diff file.txt

## 查看从近到远的提交日志

git log
git log ----pretty=oneline // 简洁显示

## 回滚

git reflog  // 记录每一次命令
git reset --hard 93c7150  // 回滚到具体的版本号

git log  // 查看版本
git reset --hard commit_id	// 回退到特定的版本号

git checkout -- file.txt //回到上一次最近的commit或者add，也就是撤销当前这部操作

git restore <文件>...  // 丢弃工作区的改动，撤销所有改动操作

git restore --staged <文件>..." // 将暂存区的文件重新放回工作区，可以先放回工作区，再撤销改动。直接在暂存区是没法修改的。

## 克隆远程仓库到本地

git clone https://github.com/adce-zcl/adce-test.git


## vscode发布到GitHub超时，使用全局代理

```
git config --global https.proxy [http://127.0.0.1:1080](http://127.0.0.1:1080/)
 
git config --global https.proxy [https://127.0.0.1:1080](https://127.0.0.1:1080/)
```



取消代理

git config --global --unset http.proxy
git config --global --unset https.proxy

## 分支操作

git branch // 查看分支

git switch -c dev //创建并切换到新分支dev

git switch dev // 切换到已有分支dev

git merge dev // 合并dev分支到当前分支

git branch -d dev // 删除dev分支

当两个分支同时修改了同一个文件的同一位置后，在合并分支的时候就会出现分支冲突，冲突后，只需要在当前分支下重新修改文件，然后add，commit就可以了。

git log --graph // 查看分支图

git branch -D dev // 强行删除没有合并的分支

## bug分支

当前分支有任务没有提交，还需要很长时间才能提交，但是有紧急任务需要马上完成。
就可以保存当前未提交的状态，先去搞定紧急任务。

git stash	// 保存当前的工作状态
// ... 中间可以随意切换分支干别的事情
git stash list // 查看保存的状态列表
git stash apply // 恢复现场但不删除
git stash drop // 删除以前保存的现场
git stash pop // 恢复的同时也删除
git cherry-pick 4c805e2 // 复制一个特定的提交到当前分支，一般是复制修复的bug到当前分支

## 标签操作

版本号太长，记不住，不如自己打标签。

git tag v1.0  // 打标签
git tag 	// 查看标签

如果某次忘了打标签，可以给以前的版本打标签：

git log --pretty=oneline --abbrev-commit	// 找到版本号
git tag v0.9 f52c633 	// 给特定的版本号打上标签

给标签打说明：

git tag -a v0.1 -m "version 0.1 released" 1094adb

标签是按照字母顺序排序的。

git show v1.0 	// 查看标签信息

标签总是和某个commit挂钩。如果这个commit既出现在master分支，又出现在dev分支，那么在这两个分支上都可以看到这个标签。

git tag -d v1.0 	// 删除标签
git push origin :refs/tags/v0.9	// 删除远程仓库的标签


git push origin v1.0		// 推送标签到远程
git push origin --tags	// 一次性推送全部未推送的标签
