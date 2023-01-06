import cs50


def main():
    # get credit card number
    card_no = cs50.get_string("Number: ")
    card_length = len(card_no)
    card_type = type_check(card_no)
    if card_type == 1:
        print("AMEX")
    if card_type == 2:
        print("MASTERCARD")
    if card_type == 3:
        print("VISA")
    if card_type == 0:
        print("INVALID")


def type_check(no):
    # 0 = Invalid
    # 1 = AE
    # 2 = Master
    # 3 = Visa
    type = 0
    valid = Luhn_check(no)
    no_length = len(no)
    first2_digit = no[0] + no[1]
    if valid == 1:
        if no_length == 15 and (first2_digit == "34" or first2_digit == "37"):
            type = 1
        if no_length == 16 and (int(first2_digit) >= 51 and int(first2_digit) <= 55):
            type = 2
        if (int(first2_digit) >= 40 and int(first2_digit) <= 49) and (no_length == 13 or no_length == 16):
            type = 3
    return type


def Luhn_check(no):
    digit_temp = 0
    length = len(no)
    for i in range(1, length, 2):
        tmp = int(no[length - i - 1]) * 2
        if tmp < 10:
            digit_temp = digit_temp + tmp
        else:
            tmp1 = int(tmp / 10)
            tmp2 = tmp % 10
            digit_temp = digit_temp + tmp1 + tmp2
    for i in range(0, length, 2):
        digit_temp = digit_temp + int(no[length - i - 1])
    if digit_temp % 10 == 0:
        result = 1
    else:
        result = 0
    return result


main()