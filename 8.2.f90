program a
  implicit none

  integer MAX_LEN
  parameter (MAX_LEN=1234)

  integer :: n = 1
  character(len=3) :: op(MAX_LEN)
  character(len=3) :: prev
  integer :: arg(MAX_LEN)
  logical :: used(MAX_LEN)
  integer :: i, ip, acc

  do
    read(*,*,end=1) op(n), arg(n)
    n = n + 1
  end do
1 n = n - 1
  do i=1,n
    prev = op(i)
    select case (op(i))
      case ("acc")
        cycle
      case ("jmp")
        op(i) = "nop"
      case ("nop")
        op(i) = "jmp"
    end select
    ip = 1
    acc = 0
    used(1:n) = .FALSE.
    do while (1 <= ip .and. ip <= n .and. .not. used(ip))
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
    if (ip == (n+1)) exit
    op(i) = prev
  end do
  write(*,*) acc

end program a
