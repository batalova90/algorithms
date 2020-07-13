program LUP_Dec
   use Environment

   implicit none
   real(R_), allocatable                        :: A(:, :), B(:), L(:,:), U(:, :), X(:), Y(:)
   integer, allocatable                         :: P(:)
   character(*), parameter                      :: input_file = "./data/input1.txt"   
   character(*), parameter                      :: output_file = "./bin/output.txt"
   integer                                      :: i = 0, In = 0, Out = 0, N = 0

  open (file=input_file, newunit = In)
  read (In, *) N
  allocate (A(N, N), B(N))
    read(In, *) (A(i, :), i = 1, N)
  read(In, *) B
  close(In)
   
  allocate (P(N), L(N, N), U(N, N), X(N), Y(N))
  P = [(i, i = 1, N)]

   call Matrix_A(A, P, N) !Формирование LUP-разложения без привлечения доп. памяти

   call LU_Matrix(A, L, U) !Формирование ед. нижнедиаг. и верхнедиаг. матрицы 
   call LUP_Solve(L, U, B, P, X)
   
   open (file=output_file, encoding=E_,  newunit=Out)
   write (out, '('//N//'f6.2)') (A(i, :), i = 1, N)
   write (Out, '(a, '//N//'f6.2, 1x, ")")') "X = (",  X
   write (Out, '('//N//'f6.2)')  Y
   write (Out, '('//N//'f6.2)') (L(i, :), i = 1, N)  
   write (Out, '('//N//'f6.2)') (U(i, :), i = 1, N)
   close (Out)

   contains
      pure subroutine Matrix_A(A, P, N)
         real(R_), intent(inout)       :: A(:, :)
         integer, intent(inout)        :: P(:)
         integer, intent(in)           :: N
         integer                       :: k , Ind
         real                          :: x
         real, allocatable             :: tmp_A(:)
         integer                       :: tmp_Index
         allocate(tmp_A(N))
         do k = 1, N
            x = 0
            Ind = MaxLoc(A(k:N, k), 1) + k - 1
                if (A(Ind, k) /= A(k, k)) then !Проверка того, что ведущий эл-т не стоит на 1-ом месте
                   tmp_A(:) = A(Ind, :)
                   A(Ind, :) = A(k, :)
                   A(k, :) = tmp_A(:)
                     
                   tmp_Index = P(k)       !Перестановка индексов матрицы свободных коэффициентов
                   P(k) = P(Ind)
                   P(Ind) = tmp_Index
                end if
             
                    A(k+1:N, k) = A(k+1:N, k)/A(k,k) !Находим дополнение Шура, разделив вектор V на опорный эл-т
                    A(k+1:N, k+1:N) = A(k+1:N, k+1:N) - Matmul(A(k+1:N, k:k), A(k:k, k+1:N))
          end do    
               
            
 end subroutine Matrix_A

 pure subroutine LU_Matrix(A, L, U)
    real(R_), intent(in)         :: A(:, :)
    real(R_), intent(inout)      :: L(:, :), U(:, :)
    integer                      :: i, j

   do j = 1, N
      do i = 1, N
         if (i > j) then
            U(i, j) = 0
            L(i, j) = A(i, j)
         else if (i == j) then
            L(i, j) = 1
            U(i, j) = A(i, j)
         else
            U(i, j) = A(i, j)
            L(i, j) = 0
         end if
      end do
   end do
      end subroutine LU_Matrix

      pure subroutine LUP_Solve(L, U, B, P, X)
   
         real, intent(in)           :: L(:, :), U(:, :), B(:)
         integer, intent(in)        :: P(:)
         real, intent(inout)        :: X(:)
         integer                    :: i, j
         real, allocatable          :: Y(:)
      
         allocate (Y(Size(X)))
   
      !Решение прямой задачи
   do i = 1, Size(X)
      y(i) = B(P(i)) - Dot_product(L(i, 1:i-1), y(1:i-1))
   end do

      !Решение обратной задачи
   do i = Size(X), 1, -1
      
      x(i) = 0
      j = 0
      do j = i+1, Size(X), 1
         x(i) = x(i) + U(i, j)*x(j) 
      end do
      x(i) = (y(i)-x(i))/U(i, i)
   
   end do

   end subroutine LUP_Solve
   
end program LUP_Dec
