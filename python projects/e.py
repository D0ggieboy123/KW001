#n = 0
# def fib(n):
#     if n == 1 or n == 2:
#         return 1
#     x = fib(n-1)
#     y = fib(n-2)
#     return x + y
# print(fib(20))
def search(nums,n):
    nums = [0,1,2,3,4,5,6]
    for i in range(len(nums)):
        if nums[i] == 4:
            print(nums[i])
            print(i)
def searchr(nums,n,index):
    #print(index)
    if nums[index] == n:
        return index
    elif index == len(nums)-1:
        return -1
    else:
        return searchr(nums,n,index+1)
nums = [1,2,3,4,5,6]
print(searchr(nums,4,0))