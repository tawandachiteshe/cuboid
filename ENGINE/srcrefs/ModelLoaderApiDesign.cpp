
class Mesh
{

    private:
        std::vector<VERTEX> m_Vertices;
        std::vector<uint32_t> m_Indices;

        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer>  m_IndexBUffer;

        Ref<VertexArray> m_VertexArray;

        void CreateBuffers(const std::vector<VERTEX>& vertices, const std::vector<uint32_t>& indices)
        {

        }

    public:

        Ref<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
        Ref<VertexBuffer> GetIndexBuffer() { return m_IndexBUffer; }

        Mesh(const std::vector<VERTEX>& vertices, const std::vector<uint32_t>& indices)
        {
            CreateBuffers(vertices, indices);
        }


        Mesh(const std::string& filepath)
        {

        }
        
        Mesh LoadFromFile(const std::string& filepath)
        {

        }


}

class ModelLoader
{
    public:
        ModelLoader(const std::string& filepath)
        {

        }

}