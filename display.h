class display {
    static void show_list_on_canvas(vector<string> headings, vector<string> content, Text &text);

    static void wrap_text(string str, int maxlen, int linespace, Text &text);

public:
    static void show_instructions();

    static void show_modes();

    static void show_coin_types();

    static void print_pair(string &heading, string &content, Text &text);
};
