# trangbee
* Bird: sử dụng các hàm load image, show image, free image, set rect và get rect,check colision ,vvv
           .Thực chất con chim chỉ đứng ở 1 tọa độ x và thay đổi tọa độ y của nó.
           .Sử dụng sự kiện bàn phím(HandleInputAction)để thay đổi tọa độ y của nó:
               +Nếu sử dụng nút PgUp trên bàn phím thì sau mỗi lần nhấn thì tọa độ y của nó sẽ + thêm một giá trị y_val = const nào đó
               +Còn nếu không sau mỗi giây y sẽ tự trừ đi một giá trị y_val = const nào đó
           .Khi mà kiếm tra va chạm (CheckColision) với các khối cột:
               +Nếu nó chạm vào cột thì màn hình dừng chuyển động(stop moving),load âm thanh và con chim rơi xuống(falling),
                khi tọa độ của con chim chạm vào nền đất thì sẽ load bức ảnh con chim thua cuộc lên.
               +Cứ mỗi lần con chim pass qua khối cột,load âm thanh thể hiện đã qua
           .Tạo 2 biến dùng để lưu điểm số và level,sau mỗi lần check pass thì điểm số được nâng lên đến 1 giới hạn nào đó, level được tăng lên 
               và sau mỗi level, thời gian di chuyển của các cột sẽ nhanh lên tăng mức độ khó cho game.
               
   * Tube: tạo 1 danh sách 6 cột nối tiếp cách nhau 1 khoảng(lưu khoảng cách bằng mảng), tọa độ ban đầu của cột trên và cột dưới khi load là phụ thuộc vào hàm random 
        mang tính ngẫu nhiên .khi cột load hết màn hình( tọa độ x nhỏ hơn 0) thì sẽ bị giải phóng, và tiếp tục được push back phía sau cột thứ 6 
        cứ liên tục như thảnh một list cột di chuyển theo tốc độ . Như em đã nói ở trên thì , sau mỗi level tốc độc di chuyển của các cột này sẽ nhanh lên.
        
   * Text: sử dụng các hàm laod text, render text, free text,vvv
         .Text dùng để xuất điểm số và level cho game trong quá trình chơi và làm menu.Sử dụng 3 màu chủ yếu là blue, pink và green.
   
   * Menu: khi bắt đầu, cần load 1 menu chơi game, nếu chọn "Play^^" (trả về giá trị false)thì sẽ bắt đầu load background,các khối cột và chơi game,
    nếu chọn "Exit"(trả về true) thì không đi được vào vòng lặp while(!quit) ở dưới( tức sẽ đóng cửa sổ game) check vị trí để khi nhấn chuột và trả
    về giá trị false(hoặc true) bằng sự kiện bàn phím/chuột, sử dụng thêm SDL_MOUSEMOTION thay đổi màu sắc của text khi di chuyển chuột vào hoặc đi ra khỏi text
          Khi người chơi thua, load 1 menu game over thể hiện người chơi đã thua cuộc, sau đó ấn exit để đóng cửa sổ game. 
          
   * Điểm số và level người chơi đạt được được cout ra màn hình .
