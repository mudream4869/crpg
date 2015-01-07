# 腳本

## 如何連接事件腳本和地圖事件

在`[Map.py]`裡面增加：

	class [EventName](Event):
        def __init__(self, syscall):
        ...

假如是物件腳本，則要寫在`objects.py`
