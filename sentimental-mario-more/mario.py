import cs50
#  Get height
while True:
    height = cs50.get_int("Height: ")
    if height > 0 and height < 8:
        break

# print the pyramids

for i in range(height):
    print("#")