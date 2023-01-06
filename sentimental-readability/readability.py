import cs50


def main():
    texts = cs50.get_string("Text: ")
    letter_c = letters_count(texts)
    word_c = words_count(texts)
    sent_c = sent_count(texts)
    cl_index = coleman_liau(letter_c, word_c, sent_c)
    if cl_index >= 16:
        print("Grade 16+")
    else:
        if (cl_index < 1):
            print("Before Grade 1")
        else:
            print("Grade ", cl_index)


def letters_count(s):
    count = 0
    s = s.lower()
    for i in range(len(s)):
        if (s[i] >= "a" and s[i] <= 'z'):
            count += 1
    return count


def words_count(s):
    count = 0
    check_set1 = ['!', '?', ',', '.', '"', ':']
    check_set2 = ['!', '?', ',', '.', '"', ':', ' ']
    for i in range(len(s)):
        c = s[i]
        if s[i] == ' ':
            if (s[i - 1] in check_set1 and i > 1):
                # dump action
                dump = 1
            else:
                count += 1
        else:
            if s[i] in check_set1:
                if (s[i - 1] in check_set2 and i > 1):
                    # dump action
                    dump = 1
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
    ave_l = float(l) / float(w) * 100.0
    ave_s = float(s) / float(w) * 100.0
    index = 0.0588 * ave_l - 0.296 * ave_s - 15.8
    x = round(index)
    return x


main()