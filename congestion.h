struct cong_level {
    int no_cars;
    char level;

    cong_level(int n, char l) {
        no_cars = n;
        level = l;
    }

    cong_level() {
        no_cars = 0;
        level = ' ';
    }
};

class congestion_heap {
    int n;
    cong_level* cars = nullptr;
    int index = 1;
    int left_c(int i) {
        return 2 * i;
    }

    int right_c(int i) {
        return 2 * i + 1;
    }

    int parent(int i) {
        return i / 2;
    }
    void heapify_down() {
        int i = 1;
        while (left_c(i) < index) {
            int largest = i;
            int left = left_c(i);
            int right = right_c(i);
            if (left < index && cars[left].no_cars > cars[largest].no_cars) {
                largest = left;
            }
            if (right < index && cars[right].no_cars > cars[largest].no_cars) {
                largest = right;
            }
            if (largest != i) {
                cong_level temp = cars[i];
                cars[i] = cars[largest];
                cars[largest] = temp;
                i = largest;
            }
            else {
                break;
            }
        }
    }

    void heapify(int i) {
        while (i > 1 && cars[i].no_cars > cars[parent(i)].no_cars) {
            cong_level temp = cars[i];
            cars[i] = cars[parent(i)];
            cars[parent(i)] = temp;
            i = parent(i);
        }
    }

public:
    congestion_heap() {
        n = 26;
        cars = new cong_level[n + 1];
        for (int i = 1; i <= n; i++) {
            cars[i].no_cars = -1;
            cars[i].level = ' ';
        }
    }
    void decrement_top() {
        cars[1].no_cars = 0;
        heapify_down();
    }
    void increment_cars(char s) {
        for (int i = 1; i <= n; i++) {
            if (cars[i].level == s) {
                cars[i].no_cars++;
                heapify(i);

            }
        }
    }
    void remove_top() {
        cars[0] = cars[index - 1];
        cars[index - 1].no_cars = -1;
        cars[index - 1].level = ' ';
        heapify_down();

    }
    void insert_car(char s, int no_cars) {
        cars[index].no_cars = no_cars;
        cars[index].level = s;
        heapify(index);
        index++;
    }

    void display_congestion_levels() {
        cout << "\n\t\t\t\t\t\t -----------------\n";
        cout << "\t\t\t\t\t\t|Congestion levels|";
        cout << "\n\t\t\t\t\t\t -----------------\n\n";
        for (int i = 1; i <= n; i++) {
            cout << "->Intersection point: " << cars[i].level
                << " , No of cars: " << cars[i].no_cars << "\n";
        }
    }

    cong_level get_max_congestion() {
        return cars[1];
    }
};