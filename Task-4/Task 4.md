## Задание 4
Что не так в этом коде? Перечислите, какие недостатки вы видите. Предложите
свой вариант рефакторинга.
    
    
    #include <stdio.h>
    class Feature
    {
        public:
        enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};
        
        Feature() : type(eUnknown), points(0) { }
        
        ~Feature()
        {
            if (points)
                delete points;
        }
        
        bool isValid()
        {
            return type != eUnknown;
        }
        
        bool read(FILE* file)
        {
            if (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType))
            return false;
            short n = 0;
            switch (type)
            {
            case eCircle: n = 3; break;
            case eTriangle: n = 6; break;
            case eSquare: n = 8; break;
            default: type = eUnknown; return false;
            }
            points = new double[n];
            if (!points)
                return false;
            return fread(&points, sizeof(double), n, file) == n*sizeof(double);
        }
        
        void draw()
        {
            switch (type)
            {
            case eCircle: drawCircle(points[0], points[1], points[2]); break;
            case eTriangle: drawPoligon(points, 6); break;
            case eSquare: drawPoligon(points, 8); break;
            }
        }
        
    protected:
        void drawCircle(double centerX, double centerY, double radius);
        void drawPoligon(double* points, int size);
        double* points;
        FeatureType type;
    };
    
    
    int main(int argc, char* argv[])
    {
        Feature feature;
        FILE* file = fopen("features.dat", "r");
        feature.read(file);
        if (!feature.isValid())
        return 1;
        return 0;
    }    
---
1) Координаты x, y, лежат вперемешку в одном массиве. 
2) `double *points;` - массив, удалять его следует при помощи `delete[]` 
3) Нет проверки значений, возвращаемого из `fopen(...)` 
4) После окончания считывания файла его не закрыли. 
5) Игнорируется значение, которое вернулось из функции `feature.read(...)`, а оно сигнализирует о том, были ли считаны 
все необходимые данные (по количеству считанных байтов) 
6) Валидность фигуры проверяется только по тому, какой у неё тип. Однако не учитывается количество вершин. Например, 
если был правильно считан верный тип фигуры, но произошла ошибка при считывании вершин, то такая фигура будет считаться корректной. 
Тоже самое происходит и в том случае, если под массив вершин вообще не смогли выделить память. 
7) "магические константы" `n=3, n=8, ...` 
--- 
Если количество типов фигур будет увеличиваться, то куда удобнее будет хранить, считывать и обрабатывать (например, рисовать) 
фигуры как наследников от общего класса. Где каждый наследник сам реализует свои функции. 

Это позволит добавлять новые типы фигуры не затрагивая код "старых". Для добавления нового типа нужно будет добавить лишь 
новый класс-наследник. 

Новые типы фигур могут разрабатываться и добавлять параллельно друг с другом, а не писать по очереди код в одну функцию. 

Каждый класс будет сам хранить своё количество вершин, что избавит код от "магических констант" `n=3, n=6, n=8`
  
 