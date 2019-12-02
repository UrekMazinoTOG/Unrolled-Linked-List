# Unrolled Linked List

Giống như mảng (array) và danh sách liên kết, unrolled linked list cũng là cấu trúc dữ liệu tuyến tính. Thay
vì lưu một phần tử dữ liệu tại mỗi node, danh sách này lưu một mảng các phần tử tại một node. Nhờ cách này,
danh sách tận dụng được lợi thế từ cả hai cấu trúc dữ liệu mảng và danh sách liên kết vì nó giảm được overhead
của danh sách liên kết khi lưu nhiều phẩn tử trong một node và có thể thêm, xoá dễ dàng. Một unrolled linked
list có thể được mô tả như hình bên dưới:

![](https://upload.wikimedia.org/wikipedia/commons/1/16/Unrolled_linked_lists_%281-8%29.PNG)

Mỗi node trong danh sách chứa một array với số lượng phần tử tối đa là maxElements. Vị trí của phần
tử trong danh sách có thể được xác định bằng tham khảo hoặc vị trí trong array. Có 2 thao tác cơ bản có thể
được thực hiện trên danh sách là phép chèn (insertion) và phép xoá (deletion)

- Chèn: để chèn một phần tử vào vị trí cụ thể, chúng ta tìm node mà phần tử cần được đặt vào và chèn
phần tử đó vào array, đồng thời tăng số phần tử trong node (numElements). Nếu array của node trước
đó đã đầy, chúng ta sẽ tạo ra một node mới ngay sau node hiện tại và chuyển phân nữa số phần tử node
hiện tại sang node mới. Thao tác này sẽ làm cho kích thước danh sách tăng lên 1.

- Xoá: để xoá một phần tử tại một vị trí cụ thể nào đó, chúng ta tìm node chứa phần tử đó và xoá nó ra khỏi
array, giảm numElements. Nếu số phần tử trong array của node nhỏ hơn ceil(maxElements/2), chúng ta
lấy 1 phần tử từ node láng giềng coho vào node hiện tại. Nếu node láng giềng chỉ có ceil(maxElements/2)
phần tử thì chúng ta sẽ nối 2 node. Nếu việc hợp nhất xảy ra thì số node trong danh sách giảm 1.

Những lợi thế của Unrolled linked list:

- Nhờ cơ chế cache, danh sách có thể thực hiện duyệt tuần tự rất nhanh. Thời gian đánh chỉ mục giảm
tuyến tính theo hệ số maxElements.

- Thực hiện các thao tác nhanh hơn danh sách lien kết thông thường, đòi hỏi ít không gian lưu trữ hơn.
