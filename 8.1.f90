program a
  implicit none

  integer MAX_LEN
  parameter (MAX_LEN=1234)

  integer :: n = 1
  character(len=3) :: op(MAX_LEN)
  integer :: arg(MAX_LEN)
  logical :: used(MAX_LEN)
  integer :: ip = 1, acc = 0

  do
    read(*,*,end=1) op(n), arg(n)
    n = n + 1
  end do
1 used(1:n) = .FALSE.
  do while (.not. used(ip))
    used(ip) = .TRUE.
    select case (op(ip))
      case ("acc")
        acc = acc + arg(ip)
        ip = ip + 1
      case ("jmp")
        ip = ip + arg(ip)
      case ("nop")
        ip = ip + 1
    end select
  end do
  write(*,*) acc

end program a
