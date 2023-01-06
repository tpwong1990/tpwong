import cs50


def main():
    texts = cs50.get_string("Text: ")


def letter_count(s):
    count = 0
    s = s.lower()
    for i in range(len(s)):
        if (s(i) >= "a" and s(i) <= 'a'):
            count += 1
    return count