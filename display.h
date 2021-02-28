class display {
    static void show_list_on_canvas(vector<string> headings, vector<string> content, Text &text);

    static void wrap_text(string &str, int maxlen, int linespace, Text &text);

    static void print_pair(string &heading, string &content, Text &text);

    static char show_coin_types();

    static char show_instructions();

public:
    static char show_modes();

    static char show_score(int);

    static void show_info();
};
