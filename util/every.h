template<size_t N>
class Every {
  private:
    size_t m_i;
    std::function<void()> m_callback;

  public:
    Every(std::function<void()> callback);
    void operator();
};
