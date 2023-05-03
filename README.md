<p align="center">
<img src="https://user-images.githubusercontent.com/71769231/235933997-8845c69e-52ee-44a7-bf82-02163f1a8efc.png" alt="Banner"></a>
</p>

<p align="center">
<img src="https://img.shields.io/badge/dependencies-python3-blue" alt="Python Badge"></a>
<img src="https://img.shields.io/badge/dependencies-gcc-orange" alt="GCC Badge"></a>
</p>

## Table Of Contents

* [About the Project](#about-the-project)
* [Acknowledgements](#acknowledgements)
* [Working](#working)
* [Usage](#usage)
* [Examples](#examples)
* [Authors](#authors)


# About the project

This is a working example of CLR and LALR example. The program takes some grammar as input and creates a CLR parse table and a LALR parse table.

The CLR parser in this project is implemented using python and the LALR parser is implemented using C++. The LALR parser processes the information generated byt he CLR parser code and uses it to generate the parse table for LALR parser.


## Acknowledgements

The CLR parser used in this project was implemented by [@SumitBamal](https://www.github.com/SumitBamal) in python. I have made some modifications in it and extended it's functionality using C++ to make a LALR parser.


## Working

You can find more about the working of the CLR parser from this repository [CLR-Parser](https://github.com/SumitBamal/CLR-Parser).

I made some modifications in the CLR parser created by [@SumitBamal](https://www.github.com/SumitBamal) so that it can output all the important information in separate text files. When you run the CLR parser the following text files will be created.
- items.txt : This file contains all the canonical items generated during the parsing of grammar.
- non-terminals.txt : This file contains all the non-terminals in the grammar.
- terminals.txt : This file contains all the terminals in the grammar.
- table.txt : This file contains information about the CLR table.

The second program for LALR parser takes it's input from the above files and works on them. Since CLR and LALR parsers are almost similar, to make the LALR parser we needed to merge the states with same grammar rules.

I implemented this using a Disjoint Set which is a special kind of tree data structure. You can read more about it here [Disjoint Set Union](https://cp-algorithms.com/data_structures/disjoint_set_union.html).

I maintained a parent and all the other states that were similar to it were merged into the parent. At the same time I also updated the names of the states so that they also have the names of their children. While merging the states if there exists any conflict then we directly quit the program by printing that the LALR table is not possible.


## Usage

Open the terminal inside the directory of this project and type the following in the terminal.

```bash
./run.sh
```

run.sh is a small script which runs two different programs. Alternatively you can also call these programs separately by executing the following commands in the terminal.

```bash
python3 CLR.py
```

After the CLR program is executed completely run the LALR program which is written in C++ by typing the following in the terminal.

```bash
g++ LALR.cpp
./a.out
```

## Examples
The program is implemented assuming that all the terminals and non-terminals will be single characters so make sure you follow this format while entering the grammar.

```bash
"A->Y1Y2..Yn" {Yi - single char} OR "A->" {epsilon}
```

After you have entered all the production rules type the following in the terminal and press enter.

```bash
end
```

After both the programs have been executed you will see a parse table for both CLR and LALR. If you have executed only the CLR program only one parse table will be present. But remember that the LALR program depends on the data generated by the CLR program so you cannot directly run LALR without running CLR first.

You can try running the following grammar in the parser or you can try your own grammar and play around it.

- CLR but not LALR

    S->Aa

    S->bAc

    S->Bc

    S->bBa

    A->d

    B->d
    
    end

- CLR and LALR

    S->(S)

    S->a

    end


## Authors

- [@importlogic](https://www.github.com/importlogic)
- [@SumitBamal](https://www.github.com/SumitBamal)
