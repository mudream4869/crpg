# CRPG

C++ 和 Python 愛好者

![Image of Yaktocat](https://github.com/mudream4869/crpg/blob/master/shot.png)

## Dependency

* Windows測試背景

    * msys2 + mingw64-x86_64
    * make
    * mingw64-glut
    * mingw64-openal
    * mingw64-python2.7

```
$ make os_switch
$ make main
```

* Mac

## 如何編譯

* 一般編譯

```
$ make os_switch
$ make main
```

* 假如需要除錯，請把`DEBUG`定義打開

```
$ make os_switch
$ make CFLAG=-DDEBUG main
```

## Some Special File Type 

* tmx 檔案:
    使用 `rapidxml` 讀取

## 測試用素材來源

* [Kaizer RTP](http://s8.photobucket.com/user/zanyzora/library/Kaizer%20RTP?sort=3&page=1)
* RpgmakerRTP 默認主角
* Youtube 音樂庫 [Audio Library](https://www.youtube.com/audiolibrary/music) 

## Coding Style

* 函數名稱：駝峰式
* 變數名稱：底線＋小寫英文

## TODO

* 說明文件: ([WIKI](https://github.com/mudream4869/crpg/wiki/CRPG介紹))
