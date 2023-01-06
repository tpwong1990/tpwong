import cs50


def main():
    # get credit card number
    card_no = cs50.get_string("Number: ")
    card_length = len(card_no)
    print(card_no[0])

def type_check(no):
    # 0 = Invalid
    # 1 = AE
    # 2 = Master
    # 3 = Visa
    valid = Luhn_check(no)
    if valid == 1:
        if 

def Luhn_check(no):
    digit_temp = 0
    for i in range(len(no) + 1, 2):
        tmp = int(no[i]) * 2
        if tmp < 10:
            digit_temp = digit_temp + tmp
        else:
            tmp1 = tmp / 10
            tmp2 = tmp % 10
            digit_temp = digit_temp + tmp1 + tmp2
    for i in range(1, len(no) + 1, 2):
        digit_temp = digit_temp + int(no(i))
    if digit_temp % 10 == 0:
        return 1
    else:
        return 0






main()