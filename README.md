# Nasdaq binary file message extractor

Extracts at random a subset of messages from the nasdaq dump file.

Usage :
```
./select -n <max_number_of_msg> -g <skip_gap_width> -f <input_file> -o <output_file>
```

Agument list :

- `-f` Path to the original nasdaq binary file.

- `-o` Path to the output file.

- `-n` ( optional ) Maximum number of messages to be selected. 
    If the argument is not provided the default value is set by the macro `MAX_MSG_CNT`

- `-g` ( optional ) Width of number of messages we might skip before selecting a new
    message to be written to the output file.
    If the argument is not provided the default value is set by the macro `RAND_GAP`


# Build

Normal build :
```
make select
```

(Optional) Build in debug mode :
```
make select debug=1
```

To clean :
```
make clean
```


