# CRPG

C++ 和 Python 愛好者

![Image of Yaktocat](https://github.com/mudream4869/crpg/blob/master/shot.png)

## Dependency

目前在`Mac OS` `Windows8` 上測試成功，`BSD`仍有[問題](https://github.com/mudream4869/crpg/issues/14)待解決．

* Mac

    請額外裝 `libvorbis`

        brew install libvorbis

* Windows測試背景

    * `msys2 + mingw64-x86_64`
    * `make`
    * `mingw64-glut`
    * `mingw64-openal`
    * `mingw64-python2.7`
    * `mingw64-libvorbis`

```
$ make os_switch
$ make main
```

## 如何編譯

* 一般編譯

```
$ make os_switch
$ make main
```

* 假如要顯示除錯訊息，請把`DEBUG`定義打開

```
$ make os_switch
$ make CFLAG=-DDEBUG main
```

* 指定編譯器或引用路徑

```
$ make os_switch CXX=(指定編譯器)
$ make main CXX=(指定編譯器) CPLUS_INCLUDE_PATH=(這裡替代成引用的路徑)
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
