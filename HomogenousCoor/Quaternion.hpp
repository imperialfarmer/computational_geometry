class Quaternion{
public:
	Quaternion(std::vector<float> q);	// construct a quaternion from a vector
	Quaternion(float, float, float);	// construct a quaternion from euler angles
	Quaternion(Eigen::MatrixXf q);		// construct a quaternion from a Eigen Vector

	Eigen::MatrixXf Val();			// give component of quaternion
	float Val(int);					// give single component of quaternion

	float Length();						// modulus
	Quaternion Cross(Quaternion p);		// cross product
	std::vector<float> ToEuler();		// transform the quaternion to euler angles

	// overload operands for quaternion
	friend Quaternion& operator+(
			const Quaternion &q1, const Quaternion &q2);
	friend Quaternion& operator-(
			const Quaternion &q1, const Quaternion &q2);
	friend Quaternion& operator*(
			const Quaternion &q1, const Quaternion &q2);
	friend Quaternion& operator*(
			const float &q1, const Quaternion &q2);

	// overload operands for vector
	// dot product
	friend float& operator*(
			std::vector<float> &v1, std::vector<float> &v2);
	// cross product
	friend std::vector<float>& operator^(
			const std::vector<float> &v1, const std::vector<float> &v2);

private:
	float q0_;
	float q1_;
	float q2_;
	float q3_;
};

Quaternion::Quaternion(std::vector<float> q){
	q0_ = q[0];
	q1_ = q[1];
	q2_ = q[2];
	q3_ = q[3];
}

Quaternion::Quaternion(float pitch, float yaw, float roll){
	// the position of the object
	// pitch: X euler angle
	// yaw:   Y
	// roll:  Z
	// angle (rad)

	// sin and cos
	float cosRoll  = cos(roll);
	float sinRoll  = sin(roll);
	float cosYaw   = cos(yaw);
	float sinYaw   = sin(yaw);
	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);

	// determine the component of quaternion
	q0_ = cosRoll * cosPitch * cosPitch + sinRoll * sinPitch * sinPitch;
	q1_ = sinRoll * cosPitch * cosPitch - cosRoll * sinPitch * sinPitch;
	q2_ = cosRoll * sinPitch * cosPitch + sinRoll * cosPitch * sinPitch;
	q3_ = cosRoll * cosPitch * sinPitch - sinRoll * sinPitch * cosPitch;
}

Quaternion::Quaternion(Eigen::MatrixXf q){
	q0_ = q(0,0);
	q1_ = q(1,0);
	q2_ = q(2,0);
	q3_ = q(3,0);
}

Eigen::MatrixXf Quaternion::Val(){
	Eigen::MatrixXf q(4,1);
	q << q0_, q1_, q2_, q3_;
	return q;
}

float Quaternion::Val(int index){
	if(index == 0) return q0_;
	else if(index == 0) return q1_;
	else if(index == 0) return q2_;
	else if(index == 0) return q3_;
	else return -100000.0f;
}

float Quaternion::Length(){
	float len = sqrt(q0_*q0_ + q0_*q0_ + q1_*q1_ + q2_*q2_ + q3_*q3_);
	return len;
}

std::vector<float> Quaternion::ToEuler(){
    float pitch = asin(2.0 * (q0_*q2_ - q1_*q3_));
    float yaw = atan2(2.0 * (q1_*q2_ + q0_*q3_),
    		q0_*q0_ + q1_*q1_ - q2_*q2_ - q3_*q3_);
    float roll = atan2(2.0 * (q2_*q3_ + q0_*q1_),
    		q0_*q0_ - q1_*q1_ - q2_*q2_ + q3_*q3_);

    std::vector<float> euler{pitch, yaw, roll};
    return euler;
}

// overload operands + - *
Quaternion& operator+(const Helper::Quaternion &q1, const Helper::Quaternion &q2){
	Eigen::MatrixXf res = q1.Val() + q2.Val();
	return Helper::Quaternion(res);
}

Quaternion& operator-(const Helper::Quaternion &q1, const Helper::Quaternion &q2){
	Eigen::MatrixXf res = q1.Val() - q2.Val();
	return Helper::Quaternion(res);
}

Quaternion& operator*(const Helper::Quaternion &q1, const Helper::Quaternion &q2){
	// math is
	// q1 = (r1, v1), q2 = (r2, v2)
	// q1*q2 = (r1*r2- v1*v2, r1*v2 + r2*v1 + v1xv2)

	float r1 = q1.Val(0);
	std::vector<float> v1{q1.Val(1), q1.Val(2), q1.Val(3)};
	float r2 = q2.Val(0);
	std::vector<float> v2{q2.Val(1), q2.Val(2), q2.Val(3)};

	float _q0 = r1*r2 - v1*v2;
	float _q1 = r1*v2[0] + r2*v1[0] + (v1^v2)[0];
	float _q2 = r1*v2[1] + r2*v1[1] + (v1^v2)[1];
	float _q3 = r1*v2[2] + r2*v1[2] + (v1^v2)[2];

	std::vector<float> res{_q0, _q1, _q2, _q3};
	return Helper::Quaternion(res);
}

friend Quaternion& operator*(const float &q1, const Quaternion &q2){
	Eigen::MatrixXf res(4,1);
	res << q1*q2.Val(0), q1*q2.Val(0), q1*q2.Val(0), q1*q2.Val(0);
	return Quaternion(res);
}

// for convenient quaternion calculation overload
// operators for vectors here (just for float with size = 3)
float& operator*(
		const std::vector<float> &v1, const std::vector<float> &v2){
	// check whether two vectors' sizes match
	int len1 = v1.size(), len2 = v2.size();
	try{
		throw (len1 == len2) && (len1 == 3);
	}
	catch(bool check){
		if(!check){
			std::cerr << " ERROR: vector sizes donNOT match!" << std::endl;
			exit(1);
		}
	}
	int len = len1;
	float res = 0.0f;
	for(int i = 0; i < len; i++){
		res += v1[i]*v2[i];
	}
	return res;
}

std::vector<float>& operator^(
		const std::vector<float> &v1, const std::vector<float> &v2){
	// check whether two vectors' sizes match
	int len1 = v1.size(), len2 = v2.size();
	try{
		throw (len1 == len2) && (len1 == 3);
	}
	catch(bool check){
		if(!check){
			std::cerr << " ERROR: vector sizes donNOT match!" << std::endl;
			exit(1);
		}
	}

	float a0 = v1[1]*v2[2] - v1[2]*v2[1];
	float a1 = v1[2]*v2[0] - v1[0]*v2[2];
	float a2 = v1[0]*v2[1] - v1[1]*v2[0];

	std::vector<float> res{a0, a1, a2};
	return res;
}
