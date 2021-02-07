# https://programmers.co.kr/learn/courses/30/lessons/42577

def check(a, b):
    if len(a) > len(b):
        tmp = a
        a = b
        b = tmp
    
    for i, v in enumerate(a):
        if b[i] != v:
            return False
    return True

def solution(phone_book):
    books = [[] for i in range(10)]
    
    for number in phone_book:
        books[int(number[0])].append(number)
        
    for numbers in books:
        for i in range(len(numbers)):
            for j in range(i+1, len(numbers)):
                if check(numbers[i], numbers[j]):
                    return False
    return True

