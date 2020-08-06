namespace kaminari
{
    void pack_complex(const Packet::Ptr& packet, const complex& data)
    {
        *packet << static_cast<bool>(data.x);
        if (static_cast<bool>(data.x))
        {
            *packet << *data.x;
        }
        *packet << static_cast<uint8_t>((data.y).size());
        for (const auto& val : data.y)
        {
            pack_spawn_data(packet, val);
        }
        *packet << data.z;
        *packet << static_cast<bool>(data.w);
        if (static_cast<bool>(data.w))
        {
            *packet << static_cast<uint8_t>((*data.w).size());
            for (const auto& val : *data.w)
            {
                *packet << val;
            }
        }
    }
    uint8_t packet_size(const complex& data)
    {
        uint8_t size = 0;
        size += sizeof(bool);
        if (static_cast<bool>(data.x));
        {
            size += sizeof_uint32();
        }
        size += sizeof(uint8_t) + (data.y).size() * sizeof_spawn_data();
        size += sizeof_int32();
        size += sizeof(bool);
        if (static_cast<bool>(data.w));
        {
            size += sizeof(uint8_t) + (*data.w).size() * sizeof_bool();
        }
    }
    void pack_spawn_data(const Packet::Ptr& packet, const spawn_data& data)
    {
        *packet << data.id;
        *packet << data.x;
        *packet << data.y;
    }
    uint8_t packet_size(const spawn_data& data)
    {
        (void)data;
        return sizeof(spawn_data);
    }
    uint8_t sizeof_spawn_data()
    {
        return sizeof(spawn_data);
    }
    bool unpack_movement(packet_reader* packet, movement& data)
    {
        data.direction = packet->read<int8>();
    }
    uint8_t packet_size(const movement& data)
    {
        (void)data;
        return sizeof(movement);
    }
    uint8_t sizeof_movement()
    {
        return sizeof(movement);
    }
    bool handle_packet(packet_reader* packet, client* client)
    {
        switch (packet->opcode())
        {
            case opcode::move:
                return handle_move(packet, client);
        }
    }
}
