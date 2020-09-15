### GitHub命令行终端命令
---
###### 1、克隆仓库
```
git clone 仓库地址
```
###### 2、推送代码到仓库
```
git init   // 初始化版本库
git add .    // 添加文件到缓存区 .代表添加文件夹下所有文件
git commit -m "提交备注" // 把添加的文件提交到版本库
git remote add origin 你的远程库地址    // 把本地库与远程库关联
git push -u origin master    // 推送代码到master分支
```
###### 3、拉取代码
```
git pull --rebase origin master    // 拉取master分支代码
git init // 初始化版本库
git add . // 添加文件到缓存区 .代表添加文件夹下所有文件
git commit -m "提交备注" // 把添加的文件提交到版本库
git remote add origin 你的远程库地址 // 把本地库与远程库关联
git push -u origin master // 推送代码到master分支
```
###### 3、拉取代码
```
git pull --rebase origin master //拉取master分支代码
```

### Bug 总结
###### 1、error: The following untracked working tree files would be overwritten by merge:
错误原因：拉取其他分支数据时出错
解决方案：

```
cd 指定目录  
git clean -d -fx
```
###### 2、remote: Forbidden fatal: unable to access 'xxxx': The requested URL returned error: 403
错误原因：  
解决方案：

```
```

###### 3、remote: HTTP Basic: Access denied
错误原因：本地git配置的用户名和密码与gitlabs上注册的用户名和密码不一致  
解决方案：

```
1. 如果账号密码有变动 用这个命令 git config –system –unset credential.helper 重新输入账号密码 应该就能解决 
2. 如果用了第一个命令 还不能解决问题那么 用这个命令：git config –global http.emptyAuth true
3. 如果还不能解决就去钥匙串中找到对应的删除掉
```

###### 4、fatal: The remote end hung up unexpectedly
错误原因：上传或者下载文件太大  
解决方案：

```
1. 把提交文件大小的上限设置大点，终端输入代码：
git config http.postBuffer 524288000
git config https.postBuffer 524288000
```