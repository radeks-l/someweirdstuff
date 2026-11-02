
data = list(map(int, input().split(' ')))
t_1 = data[0]
t_2 = data[1]
N = data[2]

arr = [-1] * (N + 1)
arr[0] = 0
arr[1] = t_1
arr[2] = t_2

def fib(n):
    if arr[n] == -1:
        arr[n] = fib(n-2) + (fib(n-1)**2)
        return arr[n];
    else:
        return arr[n];

fib(N)
print(arr[N])

