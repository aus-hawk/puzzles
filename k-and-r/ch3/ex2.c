void escape(char in[], char out[]) {
    int j = 0;
    for (int i = 0; in[i] != '\0'; ++i) {
        switch(in[i]) {
        case '\n':
            out[j++] = '\\';
            out[j++] = 'n';
            break;
        case '\t':
            out[j++] = '\\';
            out[j++] = 't';
            break;
        default:
            out[j++] = in[i];
            break;
        }
    }
    out[j] = '\0';
}

void descape(char in[], char out[]) {
    int j = 0;
    for (int i = 0; in[i] != '\0'; ++i) {
        if (in[i] == '\\') {
            switch (in[++i]) {
            case 'n':
                out[j++] = '\n';
                break;
            case 't':
                out[j++] = '\t';
                break;
            default:
                out[j++] = '\\';
                out[j++] = in[i];
                break;
            }
        } else {
            out[j++] = in[i];
        }
    }
    out[j] = '\0';
}
