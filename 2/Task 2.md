## Задание 2
Есть класс CodeGenerator, который умеет генерить код на разных языках.
Предложите рефакторинг с учетом, что количество языков будет расширяться

    class CodeGenerator
    {
    public:
        enum Lang {JAVA, C_PLUS_PLUS, PHP};
        CodeGenerator(Lang language) { _language=language; }
        std::string generateCode()
        {
            switch(_language) {
            case JAVA: //return generated java code
            case C_PLUS_PLUS: //return generated C++ code
            case PHP: //return generated PHP code
            }
            throw new std::logic_error("Bad language");
        }
        std::string someCodeRelatedThing() // used in generateCode()
        {
            switch(_language) {
            case JAVA: //return generated java-related stuff
            case C_PLUS_PLUS: //return generated C++-related stuff
            case PHP: //return generated PHP-related stuff
            }
            throw new std::logic_error("Bad language");
        }
    private:
    Lang _language;
    }
--- 
1) `enum Lang{...}` стоит сделать статической. 
2) Код сгенерированный для различных ЯП, скорее всего, будет очень сильно различаться, следовательно будет довольно мало "общих" 
участков функций где не потребовался бы `switch`. В таком случае можно написать для каждого случая свои функции, 
а `switch`-ом делать выбор функции для каждого языка. Это уменьшит влияние добавления нового языка не уже работающий код. 

3) Более хорошим вариантом будет воспользоваться динамическим полиморфизмом. Создать общий абстрактный класс-предок. 
А генераторы кода для конкретного языка создавать как его наследников. 
Так реализации функций кодогенерации ложится на потомков. Преимущества данного метода в том, что добавление нового языка 
не будет влиять на реализации генераторов для "старых". 
Если требуется, чтобы внешний интерфейс оставался прежним, то экземпляр кодогенератора можно создавать в конструкторе 
`CodeGenerator`. И там же придётся через `switch` решать какую именно реализацию следует выбрать. 