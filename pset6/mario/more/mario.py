while True:
    height = input("Height: ")
    try:
        height = int(height)
        assert height > 0 and height < 9
        break
    except (ValueError, AssertionError):
        pass

# Layers are indexed starting from 1 to improve printing.
for layer in range(1, height + 1):
    blocks = "#" * layer
    indent = " " * (height - layer)
    print(indent + blocks + "  " + blocks)
