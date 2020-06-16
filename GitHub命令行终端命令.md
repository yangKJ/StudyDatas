### GitHub命令行终端命令
---
###### 1、克隆仓库
```
git clone 仓库地址
```
###### 2、推送代码到仓库
```
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
拉取其他分支数据时出错  
解决方案：

```
cd 指定目录  
git clean -d -fx
```