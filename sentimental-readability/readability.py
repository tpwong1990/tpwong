import cs50


def main():
    texts = cs50.get_string("Text: ")


def letters_count(s):
    count = 0
    s = s.lower()
    for i in range(len(s)):
        if (s(i) >= "a" and s(i) <= 'a'):
            count += 1
    return count


def words_count(s):
    count = 0
    for i in range(len(s)):
        if s[i] == ' ':
            if ((s[i - 1] == '!' or s[i - 1] == '?' or s[i - 1] == ',' or s[i - 1] == '.' or s[i - 1] == '"' or s[i - 1] == ':') and i > 1):
            else:
                count += 1
        else:
            if (s[i] == '!' or s[i] == '?' or s[i] == ',' or s[i] == '.' or s[i] == '"' or s[i] == ':'):
            else:
                count += 1
    return count


def sent_count(s):
    count = 0
    for i in (range(len(s))):
        if (((s[i] == '!' or s[i] == '?') or s[i] == '.')):
            count += 1
    return count

def coleman_liau(l, w, s):
    



