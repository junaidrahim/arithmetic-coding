## Common Structures

```cpp
// T=char for ASCII files
// T=uint16_t for .null files
template <typename T>
struct FileData {
    std::unordered_map<char, double> probabilities;
    std::vector<T> data;

    void set_probabilities(std::string text);
    void set_data(std::string text);
    void set_probabilities(std::vector<char> c, std::vector<double> p);
    void set_data(std::vector<T> d);
};

struct NumberLine {
    std::map<uint16_t, char> m;
    uint16_t lower_limit;
    uint16_t upper_limit;
    
    NumberLine(std::unordered_map<char, double> probabilities);
    std::array<char, 5> process(const uint16_t codeword);
}
```

## FileReader

```cpp
class FileReader {
    FileData<char> read_ascii_file();
    FileData<uint16_t> read_binary_file();
};
```

## FileWriter

```cpp
class FileWriter {
    void write_ascii_file(FileData<char> f, std::string file_path);
    void write_bin_file(FileData<uint16_t> f, std::string file_path);
}
```

## Encoder

```cpp
class Encoder {
    FileData<uint16_t> encode(FileData<char> f);
}
```

## Decoder

```cpp
class Decoder {
    FileData<char> decode(FileData<uint16_t> f);
}
```




