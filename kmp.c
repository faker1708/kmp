#ifndef class_kmp
#define class_kmp

#ifndef class_string
#define class_string

int int_to_string(   int a, char*s  ){
    // 由调用者分配内存，本函数不申请堆内存
    
    printf("a = %d\n",a);

    int b;
    int c;
    int le=1;

    unsigned char temp[20];

    int minus = 0;
    if(a<0){
        minus = 1;
        a = -a;
        s[0] = '-';
        s ++;
    }

    temp[0]=0;
    while(1){
        b = a%10;
        c = a/10;   // 商

        temp[le]=b+'0';
        if(c==0){
            break;
        }else{
            le++;
            a = c;
        }
    }
    // printf("le=%d\n",le);

    
    // 倒转；
    for(int i =0 ;i<=le;i++){
        // printf("%c ",temp[i]);
        s[i] = temp[le-i];
    }


    return 0;
}

int print_string(unsigned char* s){
    unsigned int i = 0;
    while(1){
        if(s[i]==0){
            break;
        }else{
            putchar(s[i]);
        }
        i++;
    }
    return 0;
}

int get_string_length(char* s){

    int length = 0;
    if(s){

        int i = 0;  // length   
        char a = 0;
        while(1){
            a = s[i];
            if(a == 0){
                break;
            }else{
                i++;
            }

        }
        length = i;
        //printf("%d\n",i);

    }
    return length;
}

#endif /*    class_string   */
// debug


int class_kmp_print_next(char* next,int m){

    for(int i = 0;i<=m-1;i++){

        printf("%d ",next[i]);
    }
    printf("..\n");
    return 0;
}

// debug end

int class_kmp_next(char* m,int* next){
    // 给定一个字符串m，（即模式串pattern）
    int j =0; // m串的下标
    
    printf("m %s",m);


    while(1){
        printf("\n\n");
        if(m[j]==0)break;
        int f = j;
        // int t = 0;
        while(1){
            // 不断将 f坍缩到0 如果中途发现相等就打断，否则一直到0才打断
            
            printf("f %d\n",f);
            if(f==0){
                // s = -1 t = s+1
                // t = 0;
                break;
            }else{
                // f>>=0    printf("dva\n");


                int s = next[f-1];

            printf("ms %d\n",m[s]);
                if( m[s]==m[j]){
                    f = s + 1;
                    break;
                }else{
                    f = s ;
                }
            }

        }
        next[j]=f;
        j++;


    }



    return 0;
}


// 给定两个字符串，返回 模式串第一次出现在目标串中的下标，没有就返回-1
int strStr(char* n,char* m){
    // 默认n 与m的长度能用int 表示 le<= 2**31-1
    // 首先申请与m同长的int数组
    // 构造这个数组
    // 比较ni mj 如果 不等，就 i+1 j = next[j-1]

    printf("debug\n");
    int i = 0;
    int j = 0;
    int len_m = get_string_length(m);
    int* next = malloc(sizeof(int)*len_m);
    class_kmp_next(m,next);//根据模式串生成nx数组


    //class_kmp_print_next(next,len_m);
    //if(len_m>3)printf("nx3 %d\n",next[3]);

    printf("next \n");
    for(int ii = 0;ii<=len_m-1;ii++){
        printf("%d ",next[ii]);
    }
    printf("\n");


    int first_index =-1;
    int break_signal = 0;
    while(1){
        char char_a = n[i];
        char char_b = m[j];


        if(char_b==0){
            // 
            printf("模式串结束了 j %d\n",j);
            // j 指向了m的尾 \0 说明刚刚m串的尾字符 也成功匹配了。
            first_index =i -len_m;
            //break;// 找到了。
            break_signal = 1;
        }else{
            // 模式串没结束
            if(char_a ==0){
                // 目标串 n 结束了，模式串 m 还没结束 。
                first_index =-1;    // 确认找不到。
                // break;
                break_signal = 1;
            }else{
                    printf("两个串都没结束\n");
                    printf("%d %d",i,j);
                    printf("%c %c\n",char_a,char_b);
                    if(char_a == char_b){
                        //printf("%d %d\n",char_a,char_b);
                        printf("j 递增\n");
                        j++;    // 
                        i++;
                    }else{   
                        // 
                        printf("匹配失败，j 回溯\n");
                        if(j==0){
                            // j =0;
                            i++;
                        }else{
                            j = next[j-1] ;
                        }
                        printf("j %d\n",j);
                    }
                    //i++;




            }


        }
        
        
        if(break_signal ==1){
            break;
        }
    }
    return first_index;
}

int class_kmp_test(){

    char* n = "weofijxcwioefjwoeifj";
    char* m = "xc";

    n= "sadbutsad";
    m = "sad";
    printf("%s\n",m);
    printf("%s\n",n);
    int fi = strStr(n,m);
    printf("fi %d\n",fi);

    return 0;
}


#endif /*   class_kmp  */