import cs50
#  Get height
while True:
    height = cs50.get_int("Height: ")
    if height >= 1 and height <= 8:
        break