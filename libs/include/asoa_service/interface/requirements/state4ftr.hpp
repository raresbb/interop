#include <asoa/core/functionality.hpp>

/*
 * Generated with the ASOA Functionality Generator.
 * Name: state4ftr
 * ID: 5165493968636109656
 */

class state4ftr: public Functionality
{
  private:
    std::string type_name_ = "state4ftr";
    uint64_t type_id_ = 5165493968636109656;

  public:
    
    struct Data : public FuncComponentBase
    {
 
		uint8_t frame_counter;
		uint64_t tai_seconds;
		uint32_t tai_nanoseconds;
		uint8_t status;
		double pos_ell_lat_rad;
		double pos_ell_lon_rad;
		float pos_ell_h_m;
		float vel_enu_m_s[3];
		float acc_enu_m_s2[3];
		float rpy_rad[3];
		float omg_enu_rad_s[3];
		float SSA_rad;
 
		bool Data_serialize_topic(ucdrBuffer* writer, const Data* topic)
		{
		    (void) ucdr_serialize_uint8_t(writer, topic->frame_counter);
		
		    (void) ucdr_serialize_uint64_t(writer, topic->tai_seconds);
		
		    (void) ucdr_serialize_uint32_t(writer, topic->tai_nanoseconds);
		
		    (void) ucdr_serialize_uint8_t(writer, topic->status);
		
		    (void) ucdr_serialize_double(writer, topic->pos_ell_lat_rad);
		
		    (void) ucdr_serialize_double(writer, topic->pos_ell_lon_rad);
		
		    (void) ucdr_serialize_float(writer, topic->pos_ell_h_m);
		
		    (void) ucdr_serialize_array_float(writer, topic->vel_enu_m_s, sizeof(topic->vel_enu_m_s) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->acc_enu_m_s2, sizeof(topic->acc_enu_m_s2) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->rpy_rad, sizeof(topic->rpy_rad) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->omg_enu_rad_s, sizeof(topic->omg_enu_rad_s) / sizeof(float));
		
		    (void) ucdr_serialize_float(writer, topic->SSA_rad);
		
		    return !writer->error;
		}
		
		bool Data_deserialize_topic(ucdrBuffer* reader, Data* topic)
		{
		    (void) ucdr_deserialize_uint8_t(reader, &topic->frame_counter);
		
		    (void) ucdr_deserialize_uint64_t(reader, &topic->tai_seconds);
		
		    (void) ucdr_deserialize_uint32_t(reader, &topic->tai_nanoseconds);
		
		    (void) ucdr_deserialize_uint8_t(reader, &topic->status);
		
		    (void) ucdr_deserialize_double(reader, &topic->pos_ell_lat_rad);
		
		    (void) ucdr_deserialize_double(reader, &topic->pos_ell_lon_rad);
		
		    (void) ucdr_deserialize_float(reader, &topic->pos_ell_h_m);
		
		    (void) ucdr_deserialize_array_float(reader, topic->vel_enu_m_s, sizeof(topic->vel_enu_m_s) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->acc_enu_m_s2, sizeof(topic->acc_enu_m_s2) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->rpy_rad, sizeof(topic->rpy_rad) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->omg_enu_rad_s, sizeof(topic->omg_enu_rad_s) / sizeof(float));
		
		    (void) ucdr_deserialize_float(reader, &topic->SSA_rad);
		
		    return !reader->error;
		}
		
		uint32_t Data_size_of_topic(const Data* topic, uint32_t size)
		{
		    uint32_t previousSize = size;
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 8) + 8;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 8) + 8;
		
		    size += ucdr_alignment(size, 8) + 8;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->vel_enu_m_s);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->acc_enu_m_s2);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->rpy_rad);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->omg_enu_rad_s);
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    return size - previousSize;
		}
 
        uint32_t maxSize() override
        {
             
            return Data_size_of_topic(this, 0);
             
        }

        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, length);
            return Data_deserialize_topic(&ucdr_buffer, this);
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, max_size);
            bool ret = Data_serialize_topic(&ucdr_buffer, this);

            if(!ret){
                return -1;
            }else{
                return ucdr_buffer_length(&ucdr_buffer);
            }
             
        }
    } data_;
 
    struct Quality : public FuncComponentBase
    {
 
		uint8_t frame_counter;
		uint64_t tai_seconds;
		uint32_t tai_nanoseconds;
		float pos_std_enu_m[3];
		float pos_PL_enu_m[3];
		float vel_enu_std_m_s[3];
		float vel_enu_PL_m_s[3];
		float acc_enu_std_m_s2[3];
		float acc_enu_PL_m_s2[3];
		float rpy_std_rad[3];
		float rpy_PL_rad[3];
		float omg_enu_std_rad_s[3];
		float omg_enu_PL_rad_s[3];
		float SSA_std_rad;
		float SSA_PL_rad;
 
		bool Quality_serialize_topic(ucdrBuffer* writer, const Quality* topic)
		{
		    (void) ucdr_serialize_uint8_t(writer, topic->frame_counter);
		
		    (void) ucdr_serialize_uint64_t(writer, topic->tai_seconds);
		
		    (void) ucdr_serialize_uint32_t(writer, topic->tai_nanoseconds);
		
		    (void) ucdr_serialize_array_float(writer, topic->pos_std_enu_m, sizeof(topic->pos_std_enu_m) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->pos_PL_enu_m, sizeof(topic->pos_PL_enu_m) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->vel_enu_std_m_s, sizeof(topic->vel_enu_std_m_s) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->vel_enu_PL_m_s, sizeof(topic->vel_enu_PL_m_s) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->acc_enu_std_m_s2, sizeof(topic->acc_enu_std_m_s2) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->acc_enu_PL_m_s2, sizeof(topic->acc_enu_PL_m_s2) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->rpy_std_rad, sizeof(topic->rpy_std_rad) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->rpy_PL_rad, sizeof(topic->rpy_PL_rad) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->omg_enu_std_rad_s, sizeof(topic->omg_enu_std_rad_s) / sizeof(float));
		
		    (void) ucdr_serialize_array_float(writer, topic->omg_enu_PL_rad_s, sizeof(topic->omg_enu_PL_rad_s) / sizeof(float));
		
		    (void) ucdr_serialize_float(writer, topic->SSA_std_rad);
		
		    (void) ucdr_serialize_float(writer, topic->SSA_PL_rad);
		
		    return !writer->error;
		}
		
		bool Quality_deserialize_topic(ucdrBuffer* reader, Quality* topic)
		{
		    (void) ucdr_deserialize_uint8_t(reader, &topic->frame_counter);
		
		    (void) ucdr_deserialize_uint64_t(reader, &topic->tai_seconds);
		
		    (void) ucdr_deserialize_uint32_t(reader, &topic->tai_nanoseconds);
		
		    (void) ucdr_deserialize_array_float(reader, topic->pos_std_enu_m, sizeof(topic->pos_std_enu_m) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->pos_PL_enu_m, sizeof(topic->pos_PL_enu_m) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->vel_enu_std_m_s, sizeof(topic->vel_enu_std_m_s) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->vel_enu_PL_m_s, sizeof(topic->vel_enu_PL_m_s) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->acc_enu_std_m_s2, sizeof(topic->acc_enu_std_m_s2) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->acc_enu_PL_m_s2, sizeof(topic->acc_enu_PL_m_s2) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->rpy_std_rad, sizeof(topic->rpy_std_rad) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->rpy_PL_rad, sizeof(topic->rpy_PL_rad) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->omg_enu_std_rad_s, sizeof(topic->omg_enu_std_rad_s) / sizeof(float));
		
		    (void) ucdr_deserialize_array_float(reader, topic->omg_enu_PL_rad_s, sizeof(topic->omg_enu_PL_rad_s) / sizeof(float));
		
		    (void) ucdr_deserialize_float(reader, &topic->SSA_std_rad);
		
		    (void) ucdr_deserialize_float(reader, &topic->SSA_PL_rad);
		
		    return !reader->error;
		}
		
		uint32_t Quality_size_of_topic(const Quality* topic, uint32_t size)
		{
		    uint32_t previousSize = size;
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 8) + 8;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->pos_std_enu_m);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->pos_PL_enu_m);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->vel_enu_std_m_s);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->vel_enu_PL_m_s);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->acc_enu_std_m_s2);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->acc_enu_PL_m_s2);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->rpy_std_rad);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->rpy_PL_rad);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->omg_enu_std_rad_s);
		
		    size += ucdr_alignment(size, 4) + sizeof(topic->omg_enu_PL_rad_s);
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    return size - previousSize;
		}
 

        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, length);
            return Quality_deserialize_topic(&ucdr_buffer, this);
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, max_size);
            bool ret = Quality_serialize_topic(&ucdr_buffer, this);
            if (!ret)
            {
                return -1;
            }
            else
            {
                return ucdr_buffer_length(&ucdr_buffer);
            }
             
        }

        virtual uint32_t maxSize() override
        {
             
            return Quality_size_of_topic(this, 0);
             
        }

    } quality_;
 
    struct Parameter : public FuncComponentBase
    {
 
		bool dummy_flag;
 
		bool Parameter_serialize_topic(ucdrBuffer* writer, const Parameter* topic)
		{
		    (void) ucdr_serialize_bool(writer, topic->dummy_flag);
		
		    return !writer->error;
		}
		
		bool Parameter_deserialize_topic(ucdrBuffer* reader, Parameter* topic)
		{
		    (void) ucdr_deserialize_bool(reader, &topic->dummy_flag);
		
		    return !reader->error;
		}
		
		uint32_t Parameter_size_of_topic(const Parameter* topic, uint32_t size)
		{
		    uint32_t previousSize = size;
		    size += ucdr_alignment(size, 1) + 1;
		
		    return size - previousSize;
		}
 
        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, length);
            return Parameter_deserialize_topic(&ucdr_buffer, this);
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, max_size);
            bool ret = Parameter_serialize_topic(&ucdr_buffer, this);

            if (!ret)
            {
                return -1;
            }
            else
            {
                return ucdr_buffer_length(&ucdr_buffer);
            }
             
        }

        virtual uint32_t maxSize() override
        {
             
            return Parameter_size_of_topic(this, 0);
             
        }

    } parameter_;

    void Functionality()
    {
    }

    const std::string &getTypeName() override
    {
        return type_name_;
    }

    std::uint32_t getTypeID() override
    {
        return type_id_;
    }
};