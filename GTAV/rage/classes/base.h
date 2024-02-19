#pragma once

namespace rage {
    class datBase
    {
    public:
        virtual ~datBase() = default;
    }; //Size: 0x0008
    static_assert(sizeof(datBase) == 0x8);
    template<typename T, typename Base = datBase>
    class atDNode : public Base
    {
    public:
        T m_data;
        void* m_unk;
        atDNode<T, Base>* m_next;
    };

    template<typename Node>
    class atDList
    {
    public:
        Node* m_head;
        Node* m_tail;
    };

    class pgBase
    {
    public:
        virtual ~pgBase() = default;
        virtual int return_zero() = 0;
        virtual void error() = 0;

        void* unk_0000; // 0x0000
    }; //Size: 0x0008
    static_assert(sizeof(pgBase) == 0x10);
}