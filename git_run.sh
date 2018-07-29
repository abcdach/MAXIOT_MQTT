#!/bin/bash
#git pull origin master
#git rm --cached FILENAME
#
#git checkout master
#Create the branch on your local machine and switch in this branch :
#
#Push the branch on github :
#git push origin 002
#
# git checkout -b 002
#
# git push origin 002
#
# git branch
#
# git merge 002
# git push origin --delete 002
# git branch -d 002
#
#
#git add -A && git status && git commit -m "commit"
#git push -u origin 002


clear
#cp ../SERVER/MAXIOT_SERVER MAXIOT_SERVER
#exit 1
git config --global user.email "d.chkhaidze@gmail.com"
git config --global user.name  "abcdach"
git remote add origin https://github.com/abcdach/MAXIOT_MQTT.git
git add -A
git status
git commit -m "first commit"
git push -u origin master




