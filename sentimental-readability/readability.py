import cs50


def main():
    texts = cs50.get_string("Text: ")


def letter_count(s):
    count = 0
    for i in range(len(s)):
        if (s(i) >= "A" and s(i) <= 'Z') or 