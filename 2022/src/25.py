import os

s_to_d = {
        '2' : 2,
        '1' : 1,
        '0' : 0,
        '-' : -1,
        '=' : -2
}

d_to_s = {
        4 : '-',
        3 : '=',
        2 : '2',
        1 : '1',
        0 : '0'
}

def snafu_to_decimal(snafu):
    res = 0
    for i, digit in enumerate(snafu):
        res += 5**i * s_to_d[digit]
    return res

def decimal_to_snafu(decimal):
    snafu = ""
    while decimal != 0:
        remainder = decimal % 5
        decimal //= 5
        snafu = d_to_s[remainder] + snafu
        if remainder == 3 or remainder == 4:
            decimal += 1
        
        
    return snafu

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/25.in")
    
    with open(input_file_path, 'r') as f:
        data = [[char for char in line] for line in f.read().splitlines()]

    res = 0
    for snafu in data:
        res += snafu_to_decimal(snafu[::-1])

    answer = decimal_to_snafu(res)
    print(f"Final Result = {answer}")
    
     

