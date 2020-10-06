//
// Created by Jerry on 24/6/2020.
//

#ifndef CUBOID_VERTEXBUFFERLAYOUT_H
#define CUBOID_VERTEXBUFFERLAYOUT_H


namespace Cuboid
{

    class BufferLayout;

    class Shader;

    class VertexBufferLayout
    {
        public:
        virtual void Bind() = 0;

        virtual BufferLayout& GetBufferLayout() const = 0;

        ~VertexBufferLayout() = default;

        static Ref<VertexBufferLayout> Create(const BufferLayout& layout, const Ref<Shader>& shader);
    };

}


#endif //CUBOID_VERTEXBUFFERLAYOUT_H
