import codecs

if __name__ == "__main__":
    path = "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/tests/romeo_and_juliet.txt"
    with open(path, 'r') as f:
        content = f.read()
    path = "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/tests/romeo_and_juliet_encoded.txt"
    encoded_content = codecs.encode(content, 'rot_13')
    with open(path, 'w') as f:
        f.write(encoded_content)
