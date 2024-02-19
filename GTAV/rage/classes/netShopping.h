#pragma once
#include "pch.h"

namespace rage::netShopping {
    struct CNetworkShoppingMgr  {
        char _0x0000[32];
        void* m_first;
        void* m_last;
        char _0x0030[9];
        bool m_is_busy1;
        char _0x003A[14];
        bool m_is_busy2;
        char _0x0049[7];
        bool m_is_busy3;
    };

    struct netTransaction {
        int m_id;
        int m_variation;
        int m_price;
        int m_multiplier;
        int m_value;
    };

    struct netShopTransactionBasket {
        char _0x0000[0x8];
        int m_transaction_id;
        char _0x000C[0xC];
        int m_category;
        char _0x001C[0x8];
        int m_action;
        int m_target; // 4 = bank etc
        char _0x002C[0xB4];
        netTransaction m_transactions[71];
        int m_transaction_count;
    };

    struct transactionNode {
        char _0x0000[0x8];
        netShopTransactionBasket* m_transaction;
        transactionNode* m_next;
    };
}