# DS-pa1
此次作業需要模擬機場的起飛和降落情境。

機場共有四個runway，每個runway都有一個takeoff queue，且runway 2, 3, 4各多了兩個landing queue。

當有飛機要降落時，需要先放入landing queue等待；同理，起飛前也要放入takeoff queue。

當有飛機進入landing queue時，需要給進入queue的飛機兩個值: id和最長能在landing queue裡待多久的時間(1~10個time unit之間，可想成fuel level，在時間範圍內沒有降落就會墜機)；而有飛機進入takeoff queue時，只需要給id即可。

進入landing queue的id需要使用連續的奇數，而takeoff則是連續的偶數(數字皆不會重複)。

每個time unit都會有0~4架飛機需要降落，也會有0~3架飛機需要起飛，同時每個runway只能選擇一台飛機執行降落/起飛。

若有飛機沒油時，優先選擇runway 1進行迫降，若不只一台飛機沒油，則可使用其他runway迫降。

總結來說，每個time unit需要依序執行以下步驟:
step1. 把需要降落的飛機各選一個landing queue放進去並給予id及fuel level。
step2. 把需要起飛的飛機各選一個takeoff queue放進去並給予id。
step3. 檢查是否有飛機需要迫降（fuel level = 0)，若只有一台，優先選擇runway 1；若不只一台，則可以選擇其他跑道迫降(順序不限)；若同時超過四台飛機需要迫降，則會出現墜機。
step4. 若仍有空的跑道，則可選擇從對應的landing queue中選擇一架飛機進行降落或從對應的takeoff queue中選擇一架進行起飛。

當模擬完成後，需要算出這段時間機場的統計數據，如以下所示:
(a) 每個queue裡的狀態
(b) 降落的飛機平均在landing queue裡等待的時間(time unit)
(c) 起飛的飛機平均在takeoff queue裡等待的時間(time unit)
(d) 降落的飛機平均可以省下多少油(time unit)
(e) 幾架飛機需要迫降
(f) 幾架飛機墜機

作業目標就是能在模擬時間內皆不會發生墜機的前提下，仍能保持機場的良好運作(ex. 不能為了讓飛機不會墜機而造成起飛的飛機平均等待時間過長)。

此次作業基本上只要能讓每個queue的loading保持平衡就能達到不錯的效果，若有其他想法也很歡迎同學自行實作。

以下附上簡單的範例(模擬時間T=5)。
請看 program1_example.pdf

作業必須使用C或C++實作，完成作業後請把source code壓縮成zip檔上傳(學號_program1.zip)，demo時間暫定在3/28晚上，基本上只要能在模擬時間內不要發生墜機且起飛等待時間不會過長(標準後續會在公布)即可獲得很高的分數。

同時助教也會詢問幾個實作細節(ex. 如何亂數產生fuel level?)來確認code不是抄襲，請同學務必自行實作。

另外附上 output 的格式，如有問題歡迎 Teams 內or 寄信詢問
