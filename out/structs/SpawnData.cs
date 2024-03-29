using System.Collections;
using System.Collections.Generic;
namespace Kumo
{
    public class SpawnData : Kaminari.IHasId
    {
        public ulong getId()
        {
            return id;
        }
        public void setId(ulong id)
        {
            this.id = id;
        }
        public void pack(Kaminari.IMarshal marshal, Kaminari.Packet packet)
        {
            packet.getData().write((ulong)this.id);
            packet.getData().write((char)this.x);
            packet.getData().write((char)this.y);
        }
        public bool unpack(Kaminari.IMarshal marshal, Kaminari.PacketReader packet)
        {
            if (packet.bytesRead() + this.size(marshal) > packet.bufferSize())
            {
                return false;
            }
            this.id = packet.getData().readUlong();
            this.x = packet.getData().readChar();
            this.y = packet.getData().readChar();
            return true;
        }
        public int size(Kaminari.IMarshal marshal)
        {
            int size = 0;
            size += marshal.size<ulong>();
            size += marshal.size<char>();
            size += marshal.size<char>();
            return size;
        }
        public ulong id;
        public char x;
        public char y;
    }

}
