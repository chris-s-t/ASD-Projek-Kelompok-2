for(int i = 0; i < 40 ; i++){
        if (i <= 15){
            printf("|%-2d| %-40s | Rp. %-6d |   |%-2d| %-40s | Rp. %-6d |\n", i+1, makanan[i].name, makanan[i].harga, i+1, minuman[i].name, minuman[i].harga);
        }
        else if (i == 16){
            printf("|%-2d| %-40s | Rp. %-6d |   ============================================================\n",i, makanan[i].name, makanan[i].harga);
        }
        else{  
            printf("|%-2d| %-40s | Rp. %-6d |\n",i+1, makanan[i].name, makanan[i].harga);
        }
    }